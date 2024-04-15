/**
 * @file <crazyflie_speed.h>
 *
 * @author Daniel H. Stolfi
 *
 * ADARS project -- PCOG / SnT / University of Luxembourg
 */

#ifndef CRAZYFLIE_PROXIMITY_H
#define CRAZYFLIE_PROXIMITY_H

#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/generic/control_interface/ci_quadrotor_speed_actuator.h>
#include <argos3/plugins/robots/generic/control_interface/ci_positioning_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_proximity_sensor.h>

using namespace argos;

class CCrazyflieProximity : public CCI_Controller {

public:

   CCrazyflieProximity();

   virtual ~CCrazyflieProximity() {}

   virtual void Init(TConfigurationNode& t_node);

   virtual void ControlStep();

   virtual void Reset() {}

   virtual void Destroy() {}

private:
    CCI_QuadRotorSpeedActuator* m_pcSpdAct;
    CCI_PositioningSensor* m_pcPosSens;
    CCI_ProximitySensor* m_pcProximity;
};

#endif
