#include "crazyflie_proximity.h"

#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/space/space.h>

/****************************************/
/****************************************/

CCrazyflieProximity::CCrazyflieProximity() :
   m_pcSpdAct(NULL), m_pcPosSens(NULL), m_pcProximity(NULL) 
   {}

/****************************************/
/****************************************/

void CCrazyflieProximity::Init(TConfigurationNode& t_node) {
    m_pcSpdAct  = GetActuator<CCI_QuadRotorSpeedActuator>("quadrotor_speed");
    m_pcPosSens = GetSensor  <CCI_PositioningSensor     >("positioning"    );
    m_pcProximity = GetSensor <CCI_ProximitySensor      >("crazyflie_proximity");
}

/****************************************/
/****************************************/

void CCrazyflieProximity::ControlStep() {

   unsigned uTick = CSimulator::GetInstance().GetSpace().GetSimulationClock();
   std::string sId = CCI_Controller::GetId();

   /* Get readings from position sensor */
   CVector3 cPos = m_pcPosSens->GetReading().Position;
   CQuaternion cOri = m_pcPosSens->GetReading().Orientation;
   CRadians cZAngle, cYAngle, cXAngle;
   cOri.ToEulerAngles(cZAngle, cYAngle, cXAngle);
   LOG << "Position: " << std::fixed << std::setprecision(2) << cPos.GetX() << "," << cPos.GetY() << "," << cPos.GetZ();
   LOG << " : Orientation: " << ToDegrees(cXAngle.UnsignedNormalize()).GetValue() <<
                           "," << ToDegrees(cYAngle.UnsignedNormalize()).GetValue() <<
                           "," << ToDegrees(cZAngle.UnsignedNormalize()).GetValue() << std::endl;

   Real fMaxReadVal = m_pcProximity->GetReadings()[0]; // Access the first sensor's value
   UInt32 unMaxReadIdx = 0;
   if(fMaxReadVal < m_pcProximity->GetReadings()[1]) {
      fMaxReadVal = m_pcProximity->GetReadings()[1];
      unMaxReadIdx = 1;
   }
   if(fMaxReadVal < m_pcProximity->GetReadings()[7]) {
      fMaxReadVal = m_pcProximity->GetReadings()[7];
      unMaxReadIdx = 7;
   }
   if(fMaxReadVal < m_pcProximity->GetReadings()[6]) {
      fMaxReadVal = m_pcProximity->GetReadings()[6];
      unMaxReadIdx = 6;
   }

   /* Do we have an obstacle in front? */
   if(fMaxReadVal > 0.0f) {
     /* Yes, we do: avoid it */
     if(unMaxReadIdx == 0 || unMaxReadIdx == 1) {
       /* The obstacle is on the left, turn right */
       LOG << "Obstacle on the left, " << unMaxReadIdx << std::endl;;
     }
     else {
       /* The obstacle is on the left, turn right */
       LOG << "Obstacle on the right, " << unMaxReadIdx << std::endl;;
     }
   }
   else {
     /* No, we don't: go straight */
     LOG << "No obstacles, " << unMaxReadIdx << std::endl;;
   }

   /* Movement */
   if (uTick > 150) {
      m_pcSpdAct->SetLinearVelocity(CVector3::ZERO);
      m_pcSpdAct->SetRotationalSpeed(CRadians::ZERO);
   } else if (uTick > 100) {
      m_pcSpdAct->SetLinearVelocity(CVector3(0.33,-0.5,-0.33));
      m_pcSpdAct->SetRotationalSpeed(CRadians::PI_OVER_TWO);
   } else if (uTick > 80) {
      m_pcSpdAct->SetLinearVelocity(CVector3::ZERO);
      m_pcSpdAct->SetRotationalSpeed(CRadians::ZERO);
   } else if (uTick > 60) {
      m_pcSpdAct->SetLinearVelocity(CVector3(1.0,0.5,0.5));
      m_pcSpdAct->SetRotationalSpeed(-CRadians::PI_OVER_SIX);
   } else if (uTick > 40) {
      m_pcSpdAct->SetLinearVelocity(CVector3::ZERO);
      m_pcSpdAct->SetRotationalSpeed(CRadians::ZERO);
   } else if (uTick > 20) {
      m_pcSpdAct->SetLinearVelocity(CVector3(-1.0,0.0,0.0));
      m_pcSpdAct->SetRotationalSpeed(CRadians::PI_OVER_SIX);
   }
}


/****************************************/
/****************************************/

REGISTER_CONTROLLER(CCrazyflieProximity, "crazyflie_proximity_controller")
