#include "crazyflie_ground.h"

#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/space/space.h>

/****************************************/
/****************************************/

CCrazyflieGround::CCrazyflieGround() :
   m_pcPosAct(NULL),m_pcPosSens(NULL), m_pcGroundSensor(NULL) {}

/****************************************/
/****************************************/

void CCrazyflieGround::Init(TConfigurationNode& t_node) {
    m_pcPosAct  = GetActuator<CCI_QuadRotorPositionActuator>("quadrotor_position");
    m_pcPosSens = GetSensor  <CCI_PositioningSensor        >("positioning"       );
    m_pcGroundSensor = GetSensor <CCI_GroundSensor         >("crazyflie_ground"  );
}

/****************************************/
/****************************************/

void CCrazyflieGround::ControlStep() {

   unsigned uTick = CSimulator::GetInstance().GetSpace().GetSimulationClock();
   std::string sId = CCI_Controller::GetId();

    auto groundReadings = m_pcGroundSensor->GetReadings();
    for (auto reading : groundReadings) {
        LOG << "Ground Reading: " << reading << std::endl;
    }

   /* Get readings from position sensor */
   CVector3 cPos = m_pcPosSens->GetReading().Position;
   CQuaternion cOri = m_pcPosSens->GetReading().Orientation;
   CRadians cZAngle, cYAngle, cXAngle;
   cOri.ToEulerAngles(cZAngle, cYAngle, cXAngle);
   LOG << "Position: " << std::fixed << std::setprecision(2) << cPos.GetX() << "," << cPos.GetY() << "," << cPos.GetZ();
   LOG << " : Orientation: " << ToDegrees(cXAngle.UnsignedNormalize()).GetValue() <<
                           "," << ToDegrees(cYAngle.UnsignedNormalize()).GetValue() <<
                           "," << ToDegrees(cZAngle.UnsignedNormalize()).GetValue() << std::endl;

    // Real firstGroundReading = m_pcGroundSensor->GetReadings()[0];
    // LOG << "First Ground Reading: " << firstGroundReading << std::endl;


    /* Movement */
    switch (uTick) {
        case 10:
            m_pcPosAct->SetRelativePosition(CVector3(-2.0,0.0,0.0));
            m_pcPosAct->SetAbsoluteYaw(CRadians::PI);
            groundReadings = m_pcGroundSensor->GetReadings();
            break;
        case 250:
            m_pcPosAct->SetAbsolutePosition(CVector3(0.0,2.0,1.5));
            m_pcPosAct->SetRelativeYaw(-CRadians::PI);
            groundReadings = m_pcGroundSensor->GetReadings();
            break;
        case 530:
            m_pcPosAct->SetRelativePosition(CVector3(2.0,-4.0,-1.0));
            m_pcPosAct->SetAbsoluteYaw(CRadians::PI_OVER_TWO);
            groundReadings = m_pcGroundSensor->GetReadings();
            break;

    }
}

/****************************************/
/****************************************/

REGISTER_CONTROLLER(CCrazyflieGround, "crazyflie_ground_controller")
