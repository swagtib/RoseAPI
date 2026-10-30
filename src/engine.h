/*
RoseAPI - A modding API for Sub Rosa.
Copyright (C) 2026 swagtib
 
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.
 
You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef ENGINE_H
#define ENGINE_H
#include <stdint.h>
#include <roseapi.h>

void setup38offsets(uintptr_t base);

typedef void (*deleteBond_ft)(int id);
typedef void (*accountDeathTax_ft)(int id);
typedef void (*createEventBullet_ft)(int bulletType, Vector * pos, Vector * vel, int itemID);
typedef void (*createEventBulletHit_ft)(int unk, int hitType, Vector * pos, Vector * normal);
typedef void (*createEventMessage_ft)(int type, char * message, int speakerID, int distance);
typedef void (*createEventCreateVehicle_ft)(int id);
typedef void (*createEventUpdateVehicle_ft)(int vehicleID, int updateType, int partID, Vector * pos, Vector * hitVelocity);
typedef void (*createEventUpdateItemInfo_ft)(int id);
typedef void (*createEventUpdatePlayer_ft)(int id);
typedef void (*createEventUpdatePlayerFinance_ft)(int id);
typedef void (*playerDeathTax_ft)(int id);
typedef void (*createEventSound_ft)(int soundType, Vector * pos, float volume, float pitch);
typedef void (*createEventSoundItem_ft)(unsigned int soundType, int itemID, float volume, float pitch);
typedef void (*createEventUpdateCorpDoorState_ft)(int corpID, int state);
typedef void (*createEventUpdateCorpMission_ft)(int corpID, int missionID);
typedef void (*createEventUpdateElimState_ft)(int playerID, int trackerVisible, int playerTeam, int saviorPlayerID, Vector * saviorPos);
typedef void (*createEventExplosion_ft)(int type, Vector * pos);
typedef void (*playerGiveWantedLevel_ft)(int playerID, int victimPlayerID, int basePoints);
typedef void (*deleteHuman_ft)(int id);
typedef void (*deleteVehicle_ft)(int id);
typedef int (*lineIntersectTriangle_ft)(Vector * outPos, Vector * normal, float * outFraction, Vector * posA, Vector * posB, Vector * triA, Vector * triB, Vector * triC);
typedef int (*createAccountByJoinTicket_ft)(int identifier, unsigned int ticket);
typedef void (*saveAccountsServer_ft)(void);
typedef void (*aiTrafficCarDestination_ft)(int id, int a, int b, int c, int d);
typedef void (*aiTrafficCar_ft)(int id);
typedef int (*areaGetBlock_ft)(int zero, int blockX, int blockY, int blockZ);
typedef int (*areaDeleteBlock_ft)(int zero, int blockX, int blockY, int blockZ);
typedef int (*areaCreateBlock_ft)(int zero, int blockX, int blockY, int blockZ, unsigned int flags, short * unk);
typedef int (*createBondRigidBodyToLevel_ft)(int bodyID, Vector * localPos, Vector * globalPos);
typedef int (*createBondRigidBodyToRigidBody_ft)(int aBodyID, int bBodyID, Vector * aLocalPos, Vector * bLocalPos);
typedef int (*createBondRigidBodyRotRigidBody_ft)(int aBodyID, int bBodyID);
typedef void (*addCollisionRigidBodyOnRigidBody_ft)(int aBodyID, int bBodyID, Vector * aLocalPos, Vector * bLocalPos, Vector * normal, float arg6, float arg7, float arg8, float arg9);
typedef void (*addCollisionRigidBodyOnLevel_ft)(int bodyID, Vector * localPos, Vector * normal, float arg4, float arg5, float arg6, float arg7);
typedef int (*createBullet_ft)(int type, Vector * pos, Vector * vel, int playerID);
typedef void (*bulletTimeToLive_ft)(void);
typedef void (*economyCarMarket_ft)(void);
typedef void (*humanApplyDamage_ft)(int humanID, int bone, int unk, int damage);
typedef int (*lineIntersectHuman_ft)(int humanID, Vector * posA, Vector * posB, float padding);
typedef int (*itemCashGetBillValue_ft)(int itemID);
typedef int (*itemCashAddBill_ft)(int itemID, int zero, int amount);
typedef void (*itemCashRemoveBill_ft)(int itemID, int amount);
typedef int (*itemSetMemo_ft)(int itemID, char * memo);
typedef int (*itemComputerTransmitLine_ft)(int itemID, unsigned int line);
typedef void (*itemComputerIncrementLine_ft)(int id);
typedef void (*grenadeExplosion_ft)(int id);
typedef int (*linkItem_ft)(int itemID, int childItemID, int parentHumanID, int slot);
typedef void (*deleteItem_ft)(int id);
typedef void (*itemWeaponSimulation_ft)(int id);
typedef void (*vehicleApplyDamage_ft)(int vehicleID, int damage);
typedef void (*vehicleSimulateSuspensions_ft)(void);
typedef void (*humanCollisionVehicle_ft)(int humanID, int vehicleID);
typedef int (*lineIntersectVehicle_ft)(int vehicleID, Vector * posA, Vector * posB, int includeWheels);
typedef int (*createPlayer_ft)(void);
typedef void (*deletePlayer_ft)(int id);
typedef void (*prepareObjectPacket_ft)(void);
typedef void (*humanLimbInverseKinematics_ft)(int arg1, int arg2, int arg3, Vector * arg4, RotMatrix * arg5, Vector * arg6, float arg7, float arg8, float arg9, float * arg10, Vector * arg11, Vector * arg12, Vector * arg13, char arg14);
typedef int (*createRigidBody_ft)(int type, Vector * pos, RotMatrix * rot, Vector * vel, float mass, Vector * scale);
typedef int (*createHuman_ft)(Vector * pos, RotMatrix * rot, int playerID);
typedef int (*createItem_ft)(int type, Vector * pos, Vector * vel, RotMatrix * rot);
typedef int (*itemComputerInput_ft)(int itemID, unsigned int character);
typedef int (*createRope_ft)(Vector * pos, RotMatrix * rot);
typedef void (*scenarioArmHuman_ft)(int human, int weapon, int magCount);
typedef int (*createVehicle_ft)(int type, Vector * pos, Vector * vel, RotMatrix * rot, int color);
typedef void (*rigidBodySimulation_ft)(void);
typedef int (*lineIntersectLevel_ft)(Vector * posA, Vector * posB, int includeCityObjects);
typedef void (*playerAI_ft)(int id);
typedef void (*bulletSimulation_ft)(void);
typedef void (*createTraffic_ft)(int amount);
typedef void (*trafficSimulation_ft)(void);
typedef void (*physicsSimulation_ft)(void);
typedef void (*levelGenerateRaceTrack_ft)(void);
typedef void (*levelGenerateTrainRaceTrack_ft)(void);
typedef void (*calculatePlayerVoice_ft)(int connectionID, int playerID);
typedef int (*serverPlayerMessage_ft)(int playerID, char * message);
typedef void (*logicPlayerActions_ft)(int id);
typedef void (*resetGame_ft)(void);
typedef void (*logicSimulationCoop_ft)(void);
typedef void (*logicSimulationRace_ft)(void);
typedef void (*logicSimulationRound_ft)(void);
typedef void (*logicSimulationTerminator_ft)(void);
typedef void (*logicSimulationVersus_ft)(void);
typedef void (*logicSimulationWorld_ft)(void);
typedef void (*logicSimulation_ft)(void);
typedef int (*packetReceive_ft)(void);
typedef int (*sendPacket_ft)(unsigned int address, unsigned short port);
typedef int (*packetWrite_ft)(void * source, int elementSize, int elementCount);
typedef void (*serverSendConnectResponse_ft)(unsigned int address, unsigned int port, int unk, char * message);
typedef void (*serverSend_ft)(void);
typedef int (*serverReceive_ft)(void);

extern deleteBond_ft deleteBond_game;
extern accountDeathTax_ft accountDeathTax_game;
extern createEventBullet_ft createEventBullet_game;
extern createEventBulletHit_ft createEventBulletHit_game;
extern createEventMessage_ft createEventMessage_game;
extern createEventCreateVehicle_ft createEventCreateVehicle_game;
extern createEventUpdateVehicle_ft createEventUpdateVehicle_game;
extern createEventUpdateItemInfo_ft createEventUpdateItemInfo_game;
extern createEventUpdatePlayer_ft createEventUpdatePlayer_game;
extern createEventUpdatePlayerFinance_ft createEventUpdatePlayerFinance_game;
extern playerDeathTax_ft playerDeathTax_game;
extern createEventSound_ft createEventSound_game;
extern createEventSoundItem_ft createEventSoundItem_game;
extern createEventUpdateCorpDoorState_ft createEventUpdateCorpDoorState_game;
extern createEventUpdateCorpMission_ft createEventUpdateCorpMission_game;
extern createEventUpdateElimState_ft createEventUpdateElimState_game;
extern createEventExplosion_ft createEventExplosion_game;
extern playerGiveWantedLevel_ft playerGiveWantedLevel_game;
extern deleteHuman_ft deleteHuman_game;
extern deleteVehicle_ft deleteVehicle_game;
extern lineIntersectTriangle_ft lineIntersectTriangle_game;
extern createAccountByJoinTicket_ft createAccountByJoinTicket_game;
extern saveAccountsServer_ft saveAccountsServer_game;
extern aiTrafficCarDestination_ft aiTrafficCarDestination_game;
extern aiTrafficCar_ft aiTrafficCar_game;
extern areaGetBlock_ft areaGetBlock_game;
extern areaDeleteBlock_ft areaDeleteBlock_game;
extern areaCreateBlock_ft areaCreateBlock_game;
extern createBondRigidBodyToLevel_ft createBondRigidBodyToLevel_game;
extern createBondRigidBodyToRigidBody_ft createBondRigidBodyToRigidBody_game;
extern createBondRigidBodyRotRigidBody_ft createBondRigidBodyRotRigidBody_game;
extern addCollisionRigidBodyOnRigidBody_ft addCollisionRigidBodyOnRigidBody_game;
extern addCollisionRigidBodyOnLevel_ft addCollisionRigidBodyOnLevel_game;
extern createBullet_ft createBullet_game;
extern bulletTimeToLive_ft bulletTimeToLive_game;
extern economyCarMarket_ft economyCarMarket_game;
extern humanApplyDamage_ft humanApplyDamage_game;
extern lineIntersectHuman_ft lineIntersectHuman_game;
extern itemCashGetBillValue_ft itemCashGetBillValue_game;
extern itemCashAddBill_ft itemCashAddBill_game;
extern itemCashRemoveBill_ft itemCashRemoveBill_game;
extern itemSetMemo_ft itemSetMemo_game;
extern itemComputerTransmitLine_ft itemComputerTransmitLine_game;
extern itemComputerIncrementLine_ft itemComputerIncrementLine_game;
extern grenadeExplosion_ft grenadeExplosion_game;
extern linkItem_ft linkItem_game;
extern deleteItem_ft deleteItem_game;
extern itemWeaponSimulation_ft itemWeaponSimulation_game;
extern vehicleApplyDamage_ft vehicleApplyDamage_game;
extern vehicleSimulateSuspensions_ft vehicleSimulateSuspensions_game;
extern humanCollisionVehicle_ft humanCollisionVehicle_game;
extern lineIntersectVehicle_ft lineIntersectVehicle_game;
extern createPlayer_ft createPlayer_game;
extern deletePlayer_ft deletePlayer_game;
extern prepareObjectPacket_ft prepareObjectPacket_game;
extern humanLimbInverseKinematics_ft humanLimbInverseKinematics_game;
extern createRigidBody_ft createRigidBody_game;
extern createHuman_ft createHuman_game;
extern createItem_ft createItem_game;
extern itemComputerInput_ft itemComputerInput_game;
extern createRope_ft createRope_game;
extern scenarioArmHuman_ft scenarioArmHuman_game;
extern createVehicle_ft createVehicle_game;
extern rigidBodySimulation_ft rigidBodySimulation_game;
extern lineIntersectLevel_ft lineIntersectLevel_game;
extern playerAI_ft playerAI_game;
extern bulletSimulation_ft bulletSimulation_game;
extern createTraffic_ft createTraffic_game;
extern trafficSimulation_ft trafficSimulation_game;
extern physicsSimulation_ft physicsSimulation_game;
extern levelGenerateRaceTrack_ft levelGenerateRaceTrack_game;
extern levelGenerateTrainRaceTrack_ft levelGenerateTrainRaceTrack_game;
extern calculatePlayerVoice_ft calculatePlayerVoice_game;
extern serverPlayerMessage_ft serverPlayerMessage_game;
extern logicPlayerActions_ft logicPlayerActions_game;
extern resetGame_ft resetGame_game;
extern logicSimulationCoop_ft logicSimulationCoop_game;
extern logicSimulationRace_ft logicSimulationRace_game;
extern logicSimulationRound_ft logicSimulationRound_game;
extern logicSimulationTerminator_ft logicSimulationTerminator_game;
extern logicSimulationVersus_ft logicSimulationVersus_game;
extern logicSimulationWorld_ft logicSimulationWorld_game;
extern logicSimulation_ft logicSimulation_game;
extern packetReceive_ft packetReceive_game;
extern sendPacket_ft sendPacket_game;
extern packetWrite_ft packetWrite_game;
extern serverSendConnectResponse_ft serverSendConnectResponse_game;
extern serverSend_ft serverSend_game;
extern serverReceive_ft serverReceive_game;

#endif