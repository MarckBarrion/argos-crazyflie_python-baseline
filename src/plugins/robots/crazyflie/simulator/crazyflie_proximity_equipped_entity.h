/**
 * @file <argos3/plugins/robots/crazyflie/simulator/crazyflie_proximity_equipped_entity.h>
 * Based on the work of Daniel H. Stolfi and Carlo Pinciroli
 * @author Marck Herzon Barrion - <herzon.barrion@gmail.com>
 */

#ifndef CRAZYFLIE_PROXIMITY_EQUIPPED_ENTITY_H
#define CRAZYFLIE_PROXIMITY_EQUIPPED_ENTITY_H

namespace argos {
    class CCrazyflieProximityEquippedEntity;
}

#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/simulator/entity/entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <map>

namespace argos {
    
    class CCrazyflieProximityEquippedEntity : public CEntity {

    public:

        ENABLE_VTABLE();

        struct SSensor {
            typedef std::vector<SSensor*> TList;

            CVector3 Offset;
            CVector3 Direction;
            SAnchor& Anchor;

            SSensor(const CVector3& c_offset,
                    const CVector3& c_direction,
                    Real f_range,
                    SAnchor& s_anchor);
        };

    public:

        CCrazyflieProximityEquippedEntity(CComposableEntity* pc_parent);

        CCrazyflieProximityEquippedEntity(CComposableEntity* pc_parent,
                                         const std::string& str_id);
        
        virtual ~CCrazyflieProximityEquippedEntity();

        virtual void Init(TConfigurationNode& t_tree);

        virtual std::string GetTypeDescription() const {
            return "crazyflie_proximity";
        }

        virtual void Enable();

        virtual void Disable();

        inline size_t GetNumSensors() const {
            return m_tSensors.size();
        }

        inline SSensor& GetSensor(size_t un_idx) {
            return *m_tSensors[un_idx];
        }

        inline SSensor::TList& GetSensors() {
            return m_tSensors;
        }

        void AddSensor(const CVector3& c_offset,
                        const CVector3& c_direction,
                        Real f_range,
                        SAnchor& s_anchor);

        void AddSensorRing(const CVector3& c_center,
                            Real f_radius,
                            const CRadians& c_start_angle,
                            Real f_range,
                            UInt32 un_num_sensors,
                            SAnchor& s_anchor);

        void AddSensorFan(const CVector3& c_center,
                            Real f_radius,
                            const CRadians& c_start_angle,
                            const CRadians& c_end_angle,
                            Real f_range,
                            UInt32 un_num_sensors,
                            SAnchor& s_anchor);

    protected:

        /** The list of sensors */
        SSensor::TList m_tSensors;

    };
    
}

#endif