#ifndef CONDITION_TYPE_H
#define CONDITION_TYPE_H
#include <unordered_map>
#include <string>
enum class ConditionType : int {
  game_start=0,        // 比赛开始
  game_end=1,          // 比赛结束
  outpost_in_danger=2, // 前哨战半血
  outpost_off=3,       // 前哨战死亡
  in_small_energy=4,   // 小能量机关状态
  small_energy_complete=5,
  null_condition=6,
};
std::ostream & operator<<(std::ostream &os,const ConditionType &ct)
 {
      os<<static_cast<std::underlying_type<ConditionType>::type>(ct);
      return os;
 }
const std::unordered_map<std::string, ConditionType> condition_map =
            {
                    {"game_start",               ConditionType::game_start},
                    {"game_end",                 ConditionType::game_end},
                    {"outpost_in_danger",        ConditionType::outpost_in_danger},
                    {"outpost_off",              ConditionType::outpost_off},
                    {"in_small_energy",          ConditionType::in_small_energy},
                    {"small_energy_complete",     ConditionType::small_energy_complete},
                    {"null_condition",           ConditionType::null_condition},
            };
#endif //CONDITION_TYPE_H