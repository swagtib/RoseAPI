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

// Portions of this file are derived from https://github.com/jpxs-intl/RosaServer/
// Licensed under MIT
// Copyright (c) 2020 jdbool
// See THIRD_PARTY_NOTICES

#include "engine.h"
#include <stdint.h>
#include "frida-gum.h"
#include "macro.h"
#include "hooks.h"
#include "cli.h"
#include "plugin/plugin.h"
#include <unistd.h>

static gpointer resetTramp;

static void setupapi(void)
{
    if (!startCLI() || !setupPlugins() || !setuphooks()) _exit(1);
}

static void resetgameover(void)
{
    resetGame_ft tramp = resetTramp;
    tramp();
    gum_interceptor_revert(interceptor, resetGame);
    LOG("engine is ready\n");
    setupapi();
}

void engine_safety_net(void)
{
    gum_interceptor_replace(interceptor, resetGame, resetgameover, &resetTramp, NULL);
}

deleteBond_ft deleteBond;
accountDeathTax_ft accountDeathTax;
createEventBullet_ft createEventBullet;
createEventBulletHit_ft createEventBulletHit;
createEventMessage_ft createEventMessage;
createEventCreateVehicle_ft createEventCreateVehicle;
createEventUpdateVehicle_ft createEventUpdateVehicle;
createEventUpdateItemInfo_ft createEventUpdateItemInfo;
createEventUpdatePlayer_ft createEventUpdatePlayer;
createEventUpdatePlayerFinance_ft createEventUpdatePlayerFinance;
playerDeathTax_ft playerDeathTax;
createEventSound_ft createEventSound;
createEventSoundItem_ft createEventSoundItem;
createEventUpdateCorpDoorState_ft createEventUpdateCorpDoorState;
createEventUpdateCorpMission_ft createEventUpdateCorpMission;
createEventUpdateElimState_ft createEventUpdateElimState;
createEventExplosion_ft createEventExplosion;
playerGiveWantedLevel_ft playerGiveWantedLevel;
deleteHuman_ft deleteHuman;
deleteVehicle_ft deleteVehicle;
lineIntersectTriangle_ft lineIntersectTriangle;
createAccountByJoinTicket_ft createAccountByJoinTicket;
saveAccountsServer_ft saveAccountsServer;
aiTrafficCarDestination_ft aiTrafficCarDestination;
aiTrafficCar_ft aiTrafficCar;
areaGetBlock_ft areaGetBlock;
areaDeleteBlock_ft areaDeleteBlock;
areaCreateBlock_ft areaCreateBlock;
createBondRigidBodyToLevel_ft createBondRigidBodyToLevel;
createBondRigidBodyToRigidBody_ft createBondRigidBodyToRigidBody;
createBondRigidBodyRotRigidBody_ft createBondRigidBodyRotRigidBody;
addCollisionRigidBodyOnRigidBody_ft addCollisionRigidBodyOnRigidBody;
addCollisionRigidBodyOnLevel_ft addCollisionRigidBodyOnLevel;
createBullet_ft createBullet;
bulletTimeToLive_ft bulletTimeToLive;
economyCarMarket_ft economyCarMarket;
humanApplyDamage_ft humanApplyDamage;
lineIntersectHuman_ft lineIntersectHuman;
itemCashGetBillValue_ft itemCashGetBillValue;
itemCashAddBill_ft itemCashAddBill;
itemCashRemoveBill_ft itemCashRemoveBill;
itemSetMemo_ft itemSetMemo;
itemComputerTransmitLine_ft itemComputerTransmitLine;
itemComputerIncrementLine_ft itemComputerIncrementLine;
grenadeExplosion_ft grenadeExplosion;
linkItem_ft linkItem;
deleteItem_ft deleteItem;
itemWeaponSimulation_ft itemWeaponSimulation;
vehicleApplyDamage_ft vehicleApplyDamage;
vehicleSimulateSuspensions_ft vehicleSimulateSuspensions;
humanCollisionVehicle_ft humanCollisionVehicle;
lineIntersectVehicle_ft lineIntersectVehicle;
createPlayer_ft createPlayer;
deletePlayer_ft deletePlayer;
prepareObjectPacket_ft prepareObjectPacket;
humanLimbInverseKinematics_ft humanLimbInverseKinematics;
createRigidBody_ft createRigidBody;
createHuman_ft createHuman;
createItem_ft createItem;
itemComputerInput_ft itemComputerInput;
createRope_ft createRope;
scenarioArmHuman_ft scenarioArmHuman;
createVehicle_ft createVehicle;
rigidBodySimulation_ft rigidBodySimulation;
lineIntersectLevel_ft lineIntersectLevel;
playerAI_ft playerAI;
bulletSimulation_ft bulletSimulation;
createTraffic_ft createTraffic;
trafficSimulation_ft trafficSimulation;
physicsSimulation_ft physicsSimulation;
levelGenerateRaceTrack_ft levelGenerateRaceTrack;
levelGenerateTrainRaceTrack_ft levelGenerateTrainRaceTrack;
calculatePlayerVoice_ft calculatePlayerVoice;
serverPlayerMessage_ft serverPlayerMessage;
logicPlayerActions_ft logicPlayerActions;
resetGame_ft resetGame;
logicSimulationCoop_ft logicSimulationCoop;
logicSimulationRace_ft logicSimulationRace;
logicSimulationRound_ft logicSimulationRound;
logicSimulationTerminator_ft logicSimulationTerminator;
logicSimulationVersus_ft logicSimulationVersus;
logicSimulationWorld_ft logicSimulationWorld;
logicSimulation_ft logicSimulation;
packetReceive_ft packetReceive;
sendPacket_ft sendPacket;
packetWrite_ft packetWrite;
serverSendConnectResponse_ft serverSendConnectResponse;
serverSend_ft serverSend;
serverReceive_ft serverReceive;

float* gravity;
unsigned int* subVersion;
unsigned int* version;
RigidBody* bodies;
Connection* connections;
int* identifier;
Account* accounts;
VehicleType* vehicleTypes;
Event* events;
Item* items;
Voice* voices;
Human* humans;
unsigned int* sunTime;
unsigned int* numTrafficCars;
Player* players;
unsigned int* serverPort;
int* serverMaxBytesPerSecond;
char* adminPassword;
char* password;
Vehicle* vehicles;
Bond* bonds;
char* serverName;
int* isPassworded;
int* maxPlayers;
int* serverSocketEnabled;
int* packetSize;
unsigned char* packet;
int* isLevelLoaded;
char* loadedMapName;
unsigned int* numStreetIntersections;
StreetIntersection* streetIntersections;
unsigned int* numStreets;
Street* streets;
unsigned int* numBuildings;
Building* buildings;
Bullet* bullets;
int* gameType;
char* mapName;
int* Round_weekDay;
int* roundNumber;
int* gameState;
int* gameTimer;
int* ticksSinceReset;
Corporation* corporations;
int* Round_roundTime;
int* Round_startCash;
unsigned char* Round_weekly;
unsigned char* Round_bonusRatio;
int* Round_teamDamage;
int* World_traffic;
int* World_Crime_civCiv;
int* World_Crime_civTeam;
int* World_Crime_teamCiv;
int* World_Crime_teamTeam;
int* World_Crime_teamTeamInBase;
int* World_Crime_noSpawn;
int* World_startCash;
int* World_minCash;
unsigned char* World_showJoinExit;
unsigned char* World_respawnTeam;
unsigned int* numBullets;
unsigned short* numEvents;
unsigned int* numConnections;
LineIntersectResult* lineIntersectResult;
ItemType* itemTypes;
TrafficCar* trafficCars;


void init_alpha_38f(uintptr_t base) {
    deleteBond = (deleteBond_ft)(base + 0x5550);
    accountDeathTax = (accountDeathTax_ft)(base + 0x5710);
    createEventBullet = (createEventBullet_ft)(base + 0x5760);
    createEventBulletHit = (createEventBulletHit_ft)(base + 0x57F0);
    createEventMessage = (createEventMessage_ft)(base + 0x58A0);
    createEventCreateVehicle = (createEventCreateVehicle_ft)(base + 0x59C0);
    createEventUpdateVehicle = (createEventUpdateVehicle_ft)(base + 0x5A20);
    createEventUpdateItemInfo = (createEventUpdateItemInfo_ft)(base + 0x5B20);
    createEventUpdatePlayer = (createEventUpdatePlayer_ft)(base + 0x5BA0);
    createEventUpdatePlayerFinance = (createEventUpdatePlayerFinance_ft)(base + 0x5CC0);
    playerDeathTax = (playerDeathTax_ft)(base + 0x5D30);
    createEventSound = (createEventSound_ft)(base + 0x5E00);
    createEventSoundItem = (createEventSoundItem_ft)(base + 0x5E70);
    createEventUpdateCorpDoorState = (createEventUpdateCorpDoorState_ft)(base + 0x5EC0);
    createEventUpdateCorpMission = (createEventUpdateCorpMission_ft)(base + 0x6100);
    createEventUpdateElimState = (createEventUpdateElimState_ft)(base + 0x61D0);
    createEventExplosion = (createEventExplosion_ft)(base + 0x64D0);
    playerGiveWantedLevel = (playerGiveWantedLevel_ft)(base + 0x6BC0);
    deleteHuman = (deleteHuman_ft)(base + 0x6EF0);
    deleteVehicle = (deleteVehicle_ft)(base + 0x7150);
    lineIntersectTriangle = (lineIntersectTriangle_ft)(base + 0x8EF0);
    createAccountByJoinTicket = (createAccountByJoinTicket_ft)(base + 0xDB70);
    saveAccountsServer = (saveAccountsServer_ft)(base + 0xE260);
    aiTrafficCarDestination = (aiTrafficCarDestination_ft)(base + 0xF7A0);
    aiTrafficCar = (aiTrafficCar_ft)(base + 0xFE00);
    areaGetBlock = (areaGetBlock_ft)(base + 0x12B90);
    areaDeleteBlock = (areaDeleteBlock_ft)(base + 0x13800);
    areaCreateBlock = (areaCreateBlock_ft)(base + 0x19920);
    createBondRigidBodyToLevel = (createBondRigidBodyToLevel_ft)(base + 0x1AD40);
    createBondRigidBodyToRigidBody = (createBondRigidBodyToRigidBody_ft)(base + 0x1AE60);
    createBondRigidBodyRotRigidBody = (createBondRigidBodyRotRigidBody_ft)(base + 0x1B0E0);
    addCollisionRigidBodyOnRigidBody = (addCollisionRigidBodyOnRigidBody_ft)(base + 0x1B1C0);
    addCollisionRigidBodyOnLevel = (addCollisionRigidBodyOnLevel_ft)(base + 0x1B350);
    createBullet = (createBullet_ft)(base + 0x1E880);
    bulletTimeToLive = (bulletTimeToLive_ft)(base + 0x1ED50);
    economyCarMarket = (economyCarMarket_ft)(base + 0x26E70);
    humanApplyDamage = (humanApplyDamage_ft)(base + 0x2B120);
    lineIntersectHuman = (lineIntersectHuman_ft)(base + 0x3A200);
    itemCashGetBillValue = (itemCashGetBillValue_ft)(base + 0x3C840);
    itemCashAddBill = (itemCashAddBill_ft)(base + 0x3C8A0);
    itemCashRemoveBill = (itemCashRemoveBill_ft)(base + 0x3C990);
    itemSetMemo = (itemSetMemo_ft)(base + 0x3DBF0);
    itemComputerTransmitLine = (itemComputerTransmitLine_ft)(base + 0x3DD70);
    itemComputerIncrementLine = (itemComputerIncrementLine_ft)(base + 0x3E0E0);
    grenadeExplosion = (grenadeExplosion_ft)(base + 0x43410);
    linkItem = (linkItem_ft)(base + 0x460E0);
    deleteItem = (deleteItem_ft)(base + 0x48CE0);
    itemWeaponSimulation = (itemWeaponSimulation_ft)(base + 0x5D160);
    vehicleApplyDamage = (vehicleApplyDamage_ft)(base + 0x5E850);
    vehicleSimulateSuspensions = (vehicleSimulateSuspensions_ft)(base + 0x5EA90);
    humanCollisionVehicle = (humanCollisionVehicle_ft)(base + 0x68450);
    lineIntersectVehicle = (lineIntersectVehicle_ft)(base + 0x6B2A0);
    createPlayer = (createPlayer_ft)(base + 0x6D040);
    deletePlayer = (deletePlayer_ft)(base + 0x6D330);
    prepareObjectPacket = (prepareObjectPacket_ft)(base + 0x6F340);
    humanLimbInverseKinematics = (humanLimbInverseKinematics_ft)(base + 0x718D0);
    createRigidBody = (createRigidBody_ft)(base + 0x76940);
    createHuman = (createHuman_ft)(base + 0x76B80);
    createItem = (createItem_ft)(base + 0x777A0);
    itemComputerInput = (itemComputerInput_ft)(base + 0x78000);
    createRope = (createRope_ft)(base + 0x78B70);
    scenarioArmHuman = (scenarioArmHuman_ft)(base + 0x7AE30);
    createVehicle = (createVehicle_ft)(base + 0x7CF20);
    rigidBodySimulation = (rigidBodySimulation_ft)(base + 0x7F320);
    lineIntersectLevel = (lineIntersectLevel_ft)(base + 0x88CF0);
    playerAI = (playerAI_ft)(base + 0x89A60);
    bulletSimulation = (bulletSimulation_ft)(base + 0x8B4C0);
    createTraffic = (createTraffic_ft)(base + 0x9F690);
    trafficSimulation = (trafficSimulation_ft)(base + 0xA28D0);
    physicsSimulation = (physicsSimulation_ft)(base + 0xA95E0);
    levelGenerateRaceTrack = (levelGenerateRaceTrack_ft)(base + 0xAA1D0);
    levelGenerateTrainRaceTrack = (levelGenerateTrainRaceTrack_ft)(base + 0xAA5E0);
    calculatePlayerVoice = (calculatePlayerVoice_ft)(base + 0xB4C80);
    serverPlayerMessage = (serverPlayerMessage_ft)(base + 0xB9050);
    logicPlayerActions = (logicPlayerActions_ft)(base + 0xBA950);
    resetGame = (resetGame_ft)(base + 0xBF380);
    logicSimulationCoop = (logicSimulationCoop_ft)(base + 0xC1790);
    logicSimulationRace = (logicSimulationRace_ft)(base + 0xC19D0);
    logicSimulationRound = (logicSimulationRound_ft)(base + 0xC2150);
    logicSimulationTerminator = (logicSimulationTerminator_ft)(base + 0xC30D0);
    logicSimulationVersus = (logicSimulationVersus_ft)(base + 0xC4930);
    logicSimulationWorld = (logicSimulationWorld_ft)(base + 0xC54E0);
    logicSimulation = (logicSimulation_ft)(base + 0xC5F30);
    packetReceive = (packetReceive_ft)(base + 0xC7EE0);
    sendPacket = (sendPacket_ft)(base + 0xC7FF0);
    packetWrite = (packetWrite_ft)(base + 0xC8230);
    serverSendConnectResponse = (serverSendConnectResponse_ft)(base + 0xC8610);
    serverSend = (serverSend_ft)(base + 0xCD200);
    serverReceive = (serverReceive_ft)(base + 0xD0200);

    gravity = (float*)(base + 0xD874C);
    subVersion = (unsigned int*)(base + 0x2E9F04);
    version = (unsigned int*)(base + 0x2E9F08);
    bodies = (RigidBody*)(base + 0x4F1AE0);
    connections = (Connection*)(base + 0x669B20);
    identifier = (int*)(base + 0x357FD00);
    accounts = (Account*)(base + 0x357FD08);
    vehicleTypes = (VehicleType*)(base + 0x4D03560);
    events = (Event*)(base + 0x5EDCD80);
    items = (Item*)(base + 0x8117920);
    voices = (Voice*)(base + 0xAEBED80);
    humans = (Human*)(base + 0xCEFE1C8);
    sunTime = (unsigned int*)(base + 0xDFB21E0);
    numTrafficCars = (unsigned int*)(base + 0x15B253F8);
    players = (Player*)(base + 0x15B35420);
    serverPort = (unsigned int*)(base + 0x18DB02A0);
    serverMaxBytesPerSecond = (int*)(base + 0x18DB02A4);
    adminPassword = (char*)(base + 0x18DB06AC);
    password = (char*)(base + 0x18DB08AC);
    vehicles = (Vehicle*)(base + 0x1CF42740);
    bonds = (Bond*)(base + 0x24ADC1C0);
    serverName = (char*)(base + 0x250EC1D4);
    isPassworded = (int*)(base + 0x250EC5F0);
    maxPlayers = (int*)(base + 0x250EC5F4);
    serverSocketEnabled = (int*)(base + 0x39075C24);
    packetSize = (int*)(base + 0x39075C7C);
    packet = (unsigned char*)(base + 0x39075C84);
    isLevelLoaded = (int*)(base + 0x39496120);
    loadedMapName = (char*)(base + 0x39496124);
    numStreetIntersections = (unsigned int*)(base + 0x3949617C);
    streetIntersections = (StreetIntersection*)(base + 0x39496184);
    numStreets = (unsigned int*)(base + 0x394B8184);
    streets = (Street*)(base + 0x394B8188);
    numBuildings = (unsigned int*)(base + 0x3958A314);
    buildings = (Building*)(base + 0x3958A358);
    bullets = (Bullet*)(base + 0x44835BC0);
    gameType = (int*)(base + 0x44ECAACC);
    mapName = (char*)(base + 0x44ECAAD0);
    Round_weekDay = (int*)(base + 0x44ECACE4);
    roundNumber = (int*)(base + 0x44ECACE8);
    gameState = (int*)(base + 0x44ECACEC);
    gameTimer = (int*)(base + 0x44ECACF4);
    ticksSinceReset = (int*)(base + 0x44ECAD54);
    corporations = (Corporation*)(base + 0x44ECAD80);
    Round_roundTime = (int*)(base + 0x44F855CC);
    Round_startCash = (int*)(base + 0x44F855D0);
    Round_weekly = (unsigned char*)(base + 0x44F855D4);
    Round_bonusRatio = (unsigned char*)(base + 0x44F855D8);
    Round_teamDamage = (int*)(base + 0x44F855DC);
    World_traffic = (int*)(base + 0x44F855E0);
    World_Crime_civCiv = (int*)(base + 0x44F855E4);
    World_Crime_civTeam = (int*)(base + 0x44F855E8);
    World_Crime_teamCiv = (int*)(base + 0x44F855EC);
    World_Crime_teamTeam = (int*)(base + 0x44F855F0);
    World_Crime_teamTeamInBase = (int*)(base + 0x44F855F4);
    World_Crime_noSpawn = (int*)(base + 0x44F85600);
    World_startCash = (int*)(base + 0x44F85608);
    World_minCash = (int*)(base + 0x44F8560C);
    World_showJoinExit = (unsigned char*)(base + 0x44F85610);
    World_respawnTeam = (unsigned char*)(base + 0x44F85614);
    numBullets = (unsigned int*)(base + 0x45E07380);
    numEvents = (unsigned short*)(base + 0x45E07384);
    numConnections = (unsigned int*)(base + 0x45ED7DA8);
    lineIntersectResult = (LineIntersectResult*)(base + 0x569EF720);
    itemTypes = (ItemType*)(base + 0x5A60D7C0);
    trafficCars = (TrafficCar*)(base + 0x5A80BEA0);
    
    LOG("setup offsets\n");
}