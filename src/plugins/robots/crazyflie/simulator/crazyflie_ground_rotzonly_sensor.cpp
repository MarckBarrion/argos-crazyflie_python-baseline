





#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/floor_entity.h>

#include "crazyflie_ground_equipped_entity.h"
#include "crazyflie_ground_rotzonly_sensor.h"

namespace argos {

    /****************************************/
    /****************************************/

    static CRange<Real> UNIT(0.0f, 1.0f);

    /****************************************/
    /****************************************/

    CCrazyflieGroundRotZOnlySensor::CCrazyflieGroundRotZOnlySensor() :
        m_pcEmbodiedEntity(nullptr),
        m_pcFloorEntity(nullptr),
        m_pcGroundSensorEntity(nullptr),
        m_pcRNG(nullptr),
        m_bAddNoise(false),
        m_cSpace(CSimulator::GetInstance().GetSpace()) {}

    /****************************************/
    /****************************************/

    void CCrazyflieGroundRotZOnlySensor::SetRobot(CComposableEntity& c_entity) {
        m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
        m_pcGroundSensorEntity = &(c_entity.GetComponent<CCrazyflieGroundSensorEquippedEntity>("crazyflie_ground"));
        m_pcGroundSensorEntity->Enable();
        m_pcFloorEntity = &m_cSpace.GetFloorEntity();
    }

   /****************************************/
   /****************************************/

   void CCrazyflieGroundRotZOnlySensor::Init(TConfigurationNode& t_tree) {
    try {
        CCI_GroundSensor::Init(t_tree);
        /* Parse noise level */
        Real fNoiseLevel = 0.0f;
        GetNodeAttributeOrDefault(t_tree, "noise_level", fNoiseLevel, fNoiseLevel);
        if(fNoiseLevel < 0.0f) {
            THROW_ARGOSEXCEPTION("Can't specify a negative value for the noise level of the ground sensor");
        }
        else if(fNoiseLevel > 0.0f) {
            m_bAddNoise = true;
            m_cNoiseRange.Set(-fNoiseLevel, fNoiseLevel);
            m_pcRNG = CRandom::CreateRNG("argos");
        }
        m_tReadings.resize(m_pcGroundSensorEntity->GetNumSensors());
    }
    catch(CARGoSException& ex) {
        THROW_ARGOSEXCEPTION_NESTED("Initialization error in rotzonly ground sensor", ex);
    }
    /* sensor is enabled by default */
    Enable();
    }

    /****************************************/
    /****************************************/

    void CCrazyflieGroundRotZOnlySensor::Update() {
        /* sensor is disabled--nothing to do */
        if (IsDisabled()) {
            return;
        }
        /*
        * We make the assumption that the robot is rotated only wrt to Z
        */
        CRadians cRotZ, cRotY, cRotX;
        /* Set robot center center */
        CVector2 cCenterPos;
        /* Position of sensor on the ground after rototranslation */
        CVector2 cSensorPos;
        /* Go through the sensors */
        for (UInt32 i = 0; i < m_tReadings.size(); ++i) {
            CCrazyflieGroundSensorEquippedEntity::SSensor& sSens = m_pcGroundSensorEntity->GetSensor(i);
            /* Get anchor position and orientation */
            cCenterPos.Set(sSens.Anchor.Position.GetX(),
                           sSens.Anchor.Position.GetY());
            sSens.Anchor.Orientation.ToEulerAngles(cRotZ, cRotY, cRotX);
            /* Calculate sensor position on the ground */
            cSensorPos = sSens.Offset;
            cSensorPos.Rotate(cRotZ);
            cSensorPos += cCenterPos;
            /* Get the color */
            const CColor& cColor = m_pcFloorEntity->GetColorAtPoint(cSensorPos.GetX(),
                                                                    cSensorPos.GetY());
            /* Set the reading */
            m_tReadings[i] = cColor.ToGrayScale() / 255.0f;
            /* Apply noise to the sensor */
            if(m_bAddNoise) {
                m_tReadings[i] += m_pcRNG->Uniform(m_cNoiseRange);
            }
            /* Is it a BW sensor? */
            if(sSens.Type == CCrazyflieGroundSensorEquippedEntity::TYPE_BLACK_WHITE) {
                /* Yes, set 0 or 1 */
                m_tReadings[i] = m_tReadings[i] < 0.5f ? 0.0f : 1.0f;
            }
            else {
                /* No, clamp the reading between 0 and 1 */
                UNIT.TruncValue(m_tReadings[i]);
            }
        }
    }

    /****************************************/
    /****************************************/

    void CCrazyflieGroundRotZOnlySensor::Reset() {
        for(UInt32 i = 0; i < GetReadings().size(); ++i) {
            m_tReadings[i] = 0.0f;
        }
    }

    /****************************************/
    /****************************************/

    REGISTER_SENSOR(CCrazyflieGroundRotZOnlySensor,
                   "crazyflie_ground", "rot_z_only",
                   "Marck Herzon Barrion [herzon.barrion@gmail.com]",
                   "1.0",
                   "The Crazyflie ground sensor.",

                   "This sensor accesses the crazyflie ground sensor. For a complete description\n"
                   "of its usage, refer to the ci_crazyflie_ground_sensor.h interface. For the XML\n"
                   "configuration, refer to the rotzonly ground sensor.\n",

                   "Usable"
		  );

}
