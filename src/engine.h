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

extern deleteBond_ft deleteBond;
extern accountDeathTax_ft accountDeathTax;
extern createEventBullet_ft createEventBullet;
extern createEventBulletHit_ft createEventBulletHit;
extern createEventMessage_ft createEventMessage;
extern createEventCreateVehicle_ft createEventCreateVehicle;
extern createEventUpdateVehicle_ft createEventUpdateVehicle;
extern createEventUpdateItemInfo_ft createEventUpdateItemInfo;
extern createEventUpdatePlayer_ft createEventUpdatePlayer;
extern createEventUpdatePlayerFinance_ft createEventUpdatePlayerFinance;
extern playerDeathTax_ft playerDeathTax;
extern createEventSound_ft createEventSound;
extern createEventSoundItem_ft createEventSoundItem;
extern createEventUpdateCorpDoorState_ft createEventUpdateCorpDoorState;
extern createEventUpdateCorpMission_ft createEventUpdateCorpMission;
extern createEventUpdateElimState_ft createEventUpdateElimState;
extern createEventExplosion_ft createEventExplosion;
extern playerGiveWantedLevel_ft playerGiveWantedLevel;
extern deleteHuman_ft deleteHuman;
extern deleteVehicle_ft deleteVehicle;
extern lineIntersectTriangle_ft lineIntersectTriangle;
extern createAccountByJoinTicket_ft createAccountByJoinTicket;
extern saveAccountsServer_ft saveAccountsServer;
extern aiTrafficCarDestination_ft aiTrafficCarDestination;
extern aiTrafficCar_ft aiTrafficCar;
extern areaGetBlock_ft areaGetBlock;
extern areaDeleteBlock_ft areaDeleteBlock;
extern areaCreateBlock_ft areaCreateBlock;
extern createBondRigidBodyToLevel_ft createBondRigidBodyToLevel;
extern createBondRigidBodyToRigidBody_ft createBondRigidBodyToRigidBody;
extern createBondRigidBodyRotRigidBody_ft createBondRigidBodyRotRigidBody;
extern addCollisionRigidBodyOnRigidBody_ft addCollisionRigidBodyOnRigidBody;
extern addCollisionRigidBodyOnLevel_ft addCollisionRigidBodyOnLevel;
extern createBullet_ft createBullet;
extern bulletTimeToLive_ft bulletTimeToLive;
extern economyCarMarket_ft economyCarMarket;
extern humanApplyDamage_ft humanApplyDamage;
extern lineIntersectHuman_ft lineIntersectHuman;
extern itemCashGetBillValue_ft itemCashGetBillValue;
extern itemCashAddBill_ft itemCashAddBill;
extern itemCashRemoveBill_ft itemCashRemoveBill;
extern itemSetMemo_ft itemSetMemo;
extern itemComputerTransmitLine_ft itemComputerTransmitLine;
extern itemComputerIncrementLine_ft itemComputerIncrementLine;
extern grenadeExplosion_ft grenadeExplosion;
extern linkItem_ft linkItem;
extern deleteItem_ft deleteItem;
extern itemWeaponSimulation_ft itemWeaponSimulation;
extern vehicleApplyDamage_ft vehicleApplyDamage;
extern vehicleSimulateSuspensions_ft vehicleSimulateSuspensions;
extern humanCollisionVehicle_ft humanCollisionVehicle;
extern lineIntersectVehicle_ft lineIntersectVehicle;
extern createPlayer_ft createPlayer;
extern deletePlayer_ft deletePlayer;
extern prepareObjectPacket_ft prepareObjectPacket;
extern humanLimbInverseKinematics_ft humanLimbInverseKinematics;
extern createRigidBody_ft createRigidBody;
extern createHuman_ft createHuman;
extern createItem_ft createItem;
extern itemComputerInput_ft itemComputerInput;
extern createRope_ft createRope;
extern scenarioArmHuman_ft scenarioArmHuman;
extern createVehicle_ft createVehicle;
extern rigidBodySimulation_ft rigidBodySimulation;
extern lineIntersectLevel_ft lineIntersectLevel;
extern playerAI_ft playerAI;
extern bulletSimulation_ft bulletSimulation;
extern createTraffic_ft createTraffic;
extern trafficSimulation_ft trafficSimulation;
extern physicsSimulation_ft physicsSimulation;
extern levelGenerateRaceTrack_ft levelGenerateRaceTrack;
extern levelGenerateTrainRaceTrack_ft levelGenerateTrainRaceTrack;
extern calculatePlayerVoice_ft calculatePlayerVoice;
extern serverPlayerMessage_ft serverPlayerMessage;
extern logicPlayerActions_ft logicPlayerActions;
extern resetGame_ft resetGame;
extern logicSimulationCoop_ft logicSimulationCoop;
extern logicSimulationRace_ft logicSimulationRace;
extern logicSimulationRound_ft logicSimulationRound;
extern logicSimulationTerminator_ft logicSimulationTerminator;
extern logicSimulationVersus_ft logicSimulationVersus;
extern logicSimulationWorld_ft logicSimulationWorld;
extern logicSimulation_ft logicSimulation;
extern packetReceive_ft packetReceive;
extern sendPacket_ft sendPacket;
extern packetWrite_ft packetWrite;
extern serverSendConnectResponse_ft serverSendConnectResponse;
extern serverSend_ft serverSend;
extern serverReceive_ft serverReceive;


extern RigidBody* bodies;
extern Connection* connections;
extern Account* accounts;
extern VehicleType* vehicleTypes;
extern Event* events;
extern Item* items;
extern Voice* voices;
extern Human* humans;
extern unsigned int* sunTime;
extern Player* players;
extern Vehicle* vehicles;
extern Bond* bonds;
extern unsigned char* packet;
extern int* isLevelLoaded;
extern unsigned int* numStreetIntersections;
extern StreetIntersection* streetIntersections;
extern unsigned int* numStreets;
extern Street* streets;
extern unsigned int* numBuildings;
extern Building* buildings;
extern Bullet* bullets;
extern int* Round_weekDay;
extern int* roundNumber;
extern int* gameState;
extern int* gameTimer;
extern int* ticksSinceReset;
extern Corporation* corporations;
extern unsigned int* numBullets;
extern unsigned short* numEvents;
extern unsigned int* numConnections;
extern LineIntersectResult* lineIntersectResult;
extern ItemType* itemTypes;
extern TrafficCar* trafficCars;
#endif