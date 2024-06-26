/**
 * @file <argos3/plugins/robots/crazyflie/simulator/crazyflie_proximity_default_sensor.cpp>
 * Based on the work of Daniel H. Stolfi and Carlo Pinciroli
 * @author Marck Herzon Barrion - <herzon.barrion@gmail.com>
 */

#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>

#include "crazyflie_proximity_default_sensor.h"
#include "crazyflie_proximity_equipped_entity.h"

namespace argos {

    /****************************************/
    /****************************************/

    static CRange<Real> UNIT(0.0f, 1.0f);

    /****************************************/
    /****************************************/

    CCrazyflieProximityDefaultSensor::CCrazyflieProximityDefaultSensor() :
        m_pcEmbodiedEntity(nullptr),
        m_bShowRays(false),
        m_pcRNG(nullptr),
        m_bAddNoise(false),
        m_cSpace(CSimulator::GetInstance().GetSpace()) {}

    /****************************************/
    /****************************************/

    void CCrazyflieProximityDefaultSensor::SetRobot(CComposableEntity& c_entity) {
        try {
            m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
            m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));
            m_pcProximityEntity = &(c_entity.GetComponent<CCrazyflieProximityEquippedEntity>("crazyflie_proximity"));
            m_pcProximityEntity->Enable();
        }
        catch(CARGoSException& ex) {
            THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the proximity default sensor", ex);
        }
    }

    /****************************************/
    /****************************************/

    void CCrazyflieProximityDefaultSensor::Init(TConfigurationNode& t_tree) {
        try {
            CCI_ProximitySensor::Init(t_tree);
            /* Show rays? */
            GetNodeAttributeOrDefault(t_tree, "show_rays", m_bShowRays, m_bShowRays);
            /* Parse noise level */
            Real fNoiseLevel = 0.0f;
            GetNodeAttributeOrDefault(t_tree, "noise_level", fNoiseLevel, fNoiseLevel);
            if(fNoiseLevel < 0.0f) {
                THROW_ARGOSEXCEPTION("Can't specify a negative value for the noise level of the proximity sensor");
            }
            else if(fNoiseLevel > 0.0f) {
                m_bAddNoise = true;
                m_cNoiseRange.Set(-fNoiseLevel, fNoiseLevel);
                m_pcRNG = CRandom::CreateRNG("argos");
            }
            m_tReadings.resize(m_pcProximityEntity->GetNumSensors());
        }
        catch(CARGoSException& ex) {
            THROW_ARGOSEXCEPTION_NESTED("Initialization error in default proximity sensor", ex);
        }
        /* This sensor is enabled by default*/
        Enable();
    }

    /****************************************/
    /****************************************/

    void CCrazyflieProximityDefaultSensor::Update() {
        /* sensor is disabled--nothing to do */
        if (IsDisabled()) {
            return;
        }
        /* Ray used for scanning the environment for obstacles */
        CRay3 cScanningRay;
        CVector3 cRayStart, cRayEnd;
        /* Buffers to contain data about the intersection */
        SEmbodiedEntityIntersectionItem sIntersection;
        /* Go through the sensors */
        for(UInt32 i = 0; i < m_tReadings.size(); ++i) {
            /* Compute ray for sensor i*/
            cRayStart = m_pcProximityEntity->GetSensor(i).Offset;
            cRayStart.Rotate(m_pcProximityEntity->GetSensor(i).Anchor.Orientation);
            cRayStart += m_pcProximityEntity->GetSensor(i).Anchor.Position;
            cRayEnd = m_pcProximityEntity->GetSensor(i).Offset;
            cRayEnd += m_pcProximityEntity->GetSensor(i).Direction;
            cRayEnd.Rotate(m_pcProximityEntity->GetSensor(i).Anchor.Orientation);
            cRayEnd += m_pcProximityEntity->GetSensor(i).Anchor.Position;
            cScanningRay.Set(cRayStart,cRayEnd);
            /* Compute reading */
            /* Get the closest intersection */
            if(GetClosestEmbodiedEntityIntersectedByRay(sIntersection,
                                                        cScanningRay,
                                                        *m_pcEmbodiedEntity)) {
                /* There is an intersection */
                if(m_bShowRays) {
                    m_pcControllableEntity->AddIntersectionPoint(cScanningRay,
                                                                sIntersection.TOnRay);
                    m_pcControllableEntity->AddCheckedRay(true, cScanningRay);
                }
                m_tReadings[i] = CalculateReading(cScanningRay.GetDistance(sIntersection.TOnRay));
            }
            else {
                /* No intersection */
                m_tReadings[i] = 0.0f;
                if(m_bShowRays) {
                    m_pcControllableEntity->AddCheckedRay(false, cScanningRay);
                }
            }
            /* Apply noise to the sensor */
            if(m_bAddNoise) {
                m_tReadings[i] += m_pcRNG->Uniform(m_cNoiseRange);
            }
            /* Trunc the reading between 0 and 1 */
            UNIT.TruncValue(m_tReadings[i]);
        }
    }

    /****************************************/
    /****************************************/

    void CCrazyflieProximityDefaultSensor::Reset() {
        for(UInt32 i = 0; i < GetReadings().size(); ++i) {
            m_tReadings[i] = 0.0f;
        }
    }

    /****************************************/
    /****************************************/

    Real CCrazyflieProximityDefaultSensor::CalculateReading(Real f_distance) {
        return Exp(-f_distance);
    }

    /****************************************/
    /****************************************/

    REGISTER_SENSOR(CCrazyflieProximityDefaultSensor,
                   "crazyflie_proximity", "default",
                   "Marck Herzon Barrion [herzon.barrion@gmail.com]",
                   "1.0",
                   "The Crazyflie proximity sensor.",

                   "This sensor accesses the crazyflie proximity sensor. For a complete description\n"
                   "of its usage, refer to the ci_crazyflie_proximity_sensor.h interface. For the XML\n"
                   "configuration, refer to the default proximity sensor.\n",

                   "Usable"
		  );

}