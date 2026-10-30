/*
- A modding API for Sub Rosa.
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

// Now without the bootstrapping code!

#include "engine.h"
#include "roseapi.h"
#include <stdint.h>

deleteBond_ft deleteBond_game;
accountDeathTax_ft accountDeathTax_game;
createEventBullet_ft createEventBullet_game;
createEventBulletHit_ft createEventBulletHit_game;
createEventMessage_ft createEventMessage_game;
createEventCreateVehicle_ft createEventCreateVehicle_game;
createEventUpdateVehicle_ft createEventUpdateVehicle_game;
createEventUpdateItemInfo_ft createEventUpdateItemInfo_game;
createEventUpdatePlayer_ft createEventUpdatePlayer_game;
createEventUpdatePlayerFinance_ft createEventUpdatePlayerFinance_game;
playerDeathTax_ft playerDeathTax_game;
createEventSound_ft createEventSound_game;
createEventSoundItem_ft createEventSoundItem_game;
createEventUpdateCorpDoorState_ft createEventUpdateCorpDoorState_game;
createEventUpdateCorpMission_ft createEventUpdateCorpMission_game;
createEventUpdateElimState_ft createEventUpdateElimState_game;
createEventExplosion_ft createEventExplosion_game;
playerGiveWantedLevel_ft playerGiveWantedLevel_game;
deleteHuman_ft deleteHuman_game;
deleteVehicle_ft deleteVehicle_game;
lineIntersectTriangle_ft lineIntersectTriangle_game;
createAccountByJoinTicket_ft createAccountByJoinTicket_game;
saveAccountsServer_ft saveAccountsServer_game;
aiTrafficCarDestination_ft aiTrafficCarDestination_game;
aiTrafficCar_ft aiTrafficCar_game;
areaGetBlock_ft areaGetBlock_game;
areaDeleteBlock_ft areaDeleteBlock_game;
areaCreateBlock_ft areaCreateBlock_game;
createBondRigidBodyToLevel_ft createBondRigidBodyToLevel_game;
createBondRigidBodyToRigidBody_ft createBondRigidBodyToRigidBody_game;
createBondRigidBodyRotRigidBody_ft createBondRigidBodyRotRigidBody_game;
addCollisionRigidBodyOnRigidBody_ft addCollisionRigidBodyOnRigidBody_game;
addCollisionRigidBodyOnLevel_ft addCollisionRigidBodyOnLevel_game;
createBullet_ft createBullet_game;
bulletTimeToLive_ft bulletTimeToLive_game;
economyCarMarket_ft economyCarMarket_game;
humanApplyDamage_ft humanApplyDamage_game;
lineIntersectHuman_ft lineIntersectHuman_game;
itemCashGetBillValue_ft itemCashGetBillValue_game;
itemCashAddBill_ft itemCashAddBill_game;
itemCashRemoveBill_ft itemCashRemoveBill_game;
itemSetMemo_ft itemSetMemo_game;
itemComputerTransmitLine_ft itemComputerTransmitLine_game;
itemComputerIncrementLine_ft itemComputerIncrementLine_game;
grenadeExplosion_ft grenadeExplosion_game;
linkItem_ft linkItem_game;
deleteItem_ft deleteItem_game;
itemWeaponSimulation_ft itemWeaponSimulation_game;
vehicleApplyDamage_ft vehicleApplyDamage_game;
vehicleSimulateSuspensions_ft vehicleSimulateSuspensions_game;
humanCollisionVehicle_ft humanCollisionVehicle_game;
lineIntersectVehicle_ft lineIntersectVehicle_game;
createPlayer_ft createPlayer_game;
deletePlayer_ft deletePlayer_game;
prepareObjectPacket_ft prepareObjectPacket_game;
humanLimbInverseKinematics_ft humanLimbInverseKinematics_game;
createRigidBody_ft createRigidBody_game;
createHuman_ft createHuman_game;
createItem_ft createItem_game;
itemComputerInput_ft itemComputerInput_game;
createRope_ft createRope_game;
scenarioArmHuman_ft scenarioArmHuman_game;
createVehicle_ft createVehicle_game;
rigidBodySimulation_ft rigidBodySimulation_game;
lineIntersectLevel_ft lineIntersectLevel_game;
playerAI_ft playerAI_game;
bulletSimulation_ft bulletSimulation_game;
createTraffic_ft createTraffic_game;
trafficSimulation_ft trafficSimulation_game;
physicsSimulation_ft physicsSimulation_game;
levelGenerateRaceTrack_ft levelGenerateRaceTrack_game;
levelGenerateTrainRaceTrack_ft levelGenerateTrainRaceTrack_game;
calculatePlayerVoice_ft calculatePlayerVoice_game;
serverPlayerMessage_ft serverPlayerMessage_game;
logicPlayerActions_ft logicPlayerActions_game;
resetGame_ft resetGame_game;
logicSimulationCoop_ft logicSimulationCoop_game;
logicSimulationRace_ft logicSimulationRace_game;
logicSimulationRound_ft logicSimulationRound_game;
logicSimulationTerminator_ft logicSimulationTerminator_game;
logicSimulationVersus_ft logicSimulationVersus_game;
logicSimulationWorld_ft logicSimulationWorld_game;
logicSimulation_ft logicSimulation_game;
packetReceive_ft packetReceive_game;
sendPacket_ft sendPacket_game;
packetWrite_ft packetWrite_game;
serverSendConnectResponse_ft serverSendConnectResponse_game;
serverSend_ft serverSend_game;
serverReceive_ft serverReceive_game;

RigidBody* bodies;
Connection* connections;
Account* accounts;
VehicleType* vehicleTypes;
Event* events;
Item* items;
Voice* voices;
Human* humans;
Player* players;
Vehicle* vehicles;
Bond* bonds;
StreetIntersection* streetIntersections;
Street* streets;
Building* buildings;
Bullet* bullets;
Corporation* corporations;
LineIntersectResult* lineIntersectResult;
ItemType* itemTypes;
TrafficCar* trafficCars;

GameOpt GameOptions;
ServerOpt ServerOptions;

void setup38offsets(uintptr_t base) {
    deleteBond_game = (deleteBond_ft)(base + 0x5550);
    accountDeathTax_game = (accountDeathTax_ft)(base + 0x5710);
    createEventBullet_game = (createEventBullet_ft)(base + 0x5760);
    createEventBulletHit_game = (createEventBulletHit_ft)(base + 0x57F0);
    createEventMessage_game = (createEventMessage_ft)(base + 0x58A0);
    createEventCreateVehicle_game = (createEventCreateVehicle_ft)(base + 0x59C0);
    createEventUpdateVehicle_game = (createEventUpdateVehicle_ft)(base + 0x5A20);
    createEventUpdateItemInfo_game = (createEventUpdateItemInfo_ft)(base + 0x5B20);
    createEventUpdatePlayer_game = (createEventUpdatePlayer_ft)(base + 0x5BA0);
    createEventUpdatePlayerFinance_game = (createEventUpdatePlayerFinance_ft)(base + 0x5CC0);
    playerDeathTax_game = (playerDeathTax_ft)(base + 0x5D30);
    createEventSound_game = (createEventSound_ft)(base + 0x5E00);
    createEventSoundItem_game = (createEventSoundItem_ft)(base + 0x5E70);
    createEventUpdateCorpDoorState_game = (createEventUpdateCorpDoorState_ft)(base + 0x5EC0);
    createEventUpdateCorpMission_game = (createEventUpdateCorpMission_ft)(base + 0x6100);
    createEventUpdateElimState_game = (createEventUpdateElimState_ft)(base + 0x61D0);
    createEventExplosion_game = (createEventExplosion_ft)(base + 0x64D0);
    playerGiveWantedLevel_game = (playerGiveWantedLevel_ft)(base + 0x6BC0);
    deleteHuman_game = (deleteHuman_ft)(base + 0x6EF0);
    deleteVehicle_game = (deleteVehicle_ft)(base + 0x7150);
    lineIntersectTriangle_game = (lineIntersectTriangle_ft)(base + 0x8EF0);
    createAccountByJoinTicket_game = (createAccountByJoinTicket_ft)(base + 0xDB70);
    saveAccountsServer_game = (saveAccountsServer_ft)(base + 0xE260);
    aiTrafficCarDestination_game = (aiTrafficCarDestination_ft)(base + 0xF7A0);
    aiTrafficCar_game = (aiTrafficCar_ft)(base + 0xFE00);
    areaGetBlock_game = (areaGetBlock_ft)(base + 0x12B90);
    areaDeleteBlock_game = (areaDeleteBlock_ft)(base + 0x13800);
    areaCreateBlock_game = (areaCreateBlock_ft)(base + 0x19920);
    createBondRigidBodyToLevel_game = (createBondRigidBodyToLevel_ft)(base + 0x1AD40);
    createBondRigidBodyToRigidBody_game = (createBondRigidBodyToRigidBody_ft)(base + 0x1AE60);
    createBondRigidBodyRotRigidBody_game = (createBondRigidBodyRotRigidBody_ft)(base + 0x1B0E0);
    addCollisionRigidBodyOnRigidBody_game = (addCollisionRigidBodyOnRigidBody_ft)(base + 0x1B1C0);
    addCollisionRigidBodyOnLevel_game = (addCollisionRigidBodyOnLevel_ft)(base + 0x1B350);
    createBullet_game = (createBullet_ft)(base + 0x1E880);
    bulletTimeToLive_game = (bulletTimeToLive_ft)(base + 0x1ED50);
    economyCarMarket_game = (economyCarMarket_ft)(base + 0x26E70);
    humanApplyDamage_game = (humanApplyDamage_ft)(base + 0x2B120);
    lineIntersectHuman_game = (lineIntersectHuman_ft)(base + 0x3A200);
    itemCashGetBillValue_game = (itemCashGetBillValue_ft)(base + 0x3C840);
    itemCashAddBill_game = (itemCashAddBill_ft)(base + 0x3C8A0);
    itemCashRemoveBill_game = (itemCashRemoveBill_ft)(base + 0x3C990);
    itemSetMemo_game = (itemSetMemo_ft)(base + 0x3DBF0);
    itemComputerTransmitLine_game = (itemComputerTransmitLine_ft)(base + 0x3DD70);
    itemComputerIncrementLine_game = (itemComputerIncrementLine_ft)(base + 0x3E0E0);
    grenadeExplosion_game = (grenadeExplosion_ft)(base + 0x43410);
    linkItem_game = (linkItem_ft)(base + 0x460E0);
    deleteItem_game = (deleteItem_ft)(base + 0x48CE0);
    itemWeaponSimulation_game = (itemWeaponSimulation_ft)(base + 0x5D160);
    vehicleApplyDamage_game = (vehicleApplyDamage_ft)(base + 0x5E850);
    vehicleSimulateSuspensions_game = (vehicleSimulateSuspensions_ft)(base + 0x5EA90);
    humanCollisionVehicle_game = (humanCollisionVehicle_ft)(base + 0x68450);
    lineIntersectVehicle_game = (lineIntersectVehicle_ft)(base + 0x6B2A0);
    createPlayer_game = (createPlayer_ft)(base + 0x6D040);
    deletePlayer_game = (deletePlayer_ft)(base + 0x6D330);
    prepareObjectPacket_game = (prepareObjectPacket_ft)(base + 0x6F340);
    humanLimbInverseKinematics_game = (humanLimbInverseKinematics_ft)(base + 0x718D0);
    createRigidBody_game = (createRigidBody_ft)(base + 0x76940);
    createHuman_game = (createHuman_ft)(base + 0x76B80);
    createItem_game = (createItem_ft)(base + 0x777A0);
    itemComputerInput_game = (itemComputerInput_ft)(base + 0x78000);
    createRope_game = (createRope_ft)(base + 0x78B70);
    scenarioArmHuman_game = (scenarioArmHuman_ft)(base + 0x7AE30);
    createVehicle_game = (createVehicle_ft)(base + 0x7CF20);
    rigidBodySimulation_game = (rigidBodySimulation_ft)(base + 0x7F320);
    lineIntersectLevel_game = (lineIntersectLevel_ft)(base + 0x88CF0);
    playerAI_game = (playerAI_ft)(base + 0x89A60);
    bulletSimulation_game = (bulletSimulation_ft)(base + 0x8B4C0);
    createTraffic_game = (createTraffic_ft)(base + 0x9F690);
    trafficSimulation_game = (trafficSimulation_ft)(base + 0xA28D0);
    physicsSimulation_game = (physicsSimulation_ft)(base + 0xA95E0);
    levelGenerateRaceTrack_game = (levelGenerateRaceTrack_ft)(base + 0xAA1D0);
    levelGenerateTrainRaceTrack_game = (levelGenerateTrainRaceTrack_ft)(base + 0xAA5E0);
    calculatePlayerVoice_game = (calculatePlayerVoice_ft)(base + 0xB4C80);
    serverPlayerMessage_game = (serverPlayerMessage_ft)(base + 0xB9050);
    logicPlayerActions_game = (logicPlayerActions_ft)(base + 0xBA950);
    resetGame_game = (resetGame_ft)(base + 0xBF380);
    logicSimulationCoop_game = (logicSimulationCoop_ft)(base + 0xC1790);
    logicSimulationRace_game = (logicSimulationRace_ft)(base + 0xC19D0);
    logicSimulationRound_game = (logicSimulationRound_ft)(base + 0xC2150);
    logicSimulationTerminator_game = (logicSimulationTerminator_ft)(base + 0xC30D0);
    logicSimulationVersus_game = (logicSimulationVersus_ft)(base + 0xC4930);
    logicSimulationWorld_game = (logicSimulationWorld_ft)(base + 0xC54E0);
    logicSimulation_game = (logicSimulation_ft)(base + 0xC5F30);
    packetReceive_game = (packetReceive_ft)(base + 0xC7EE0);
    sendPacket_game = (sendPacket_ft)(base + 0xC7FF0);
    packetWrite_game = (packetWrite_ft)(base + 0xC8230);
    serverSendConnectResponse_game = (serverSendConnectResponse_ft)(base + 0xC8610);
    serverSend_game = (serverSend_ft)(base + 0xCD200);
    serverReceive_game = (serverReceive_ft)(base + 0xD0200);

    ServerOptions.gravity = (float*)(base + 0xD874C);
    ServerOptions.subVersion = (unsigned int*)(base + 0x2E9F04);
    ServerOptions.version = (unsigned int*)(base + 0x2E9F08);
    bodies = (RigidBody*)(base + 0x4F1AE0);
    connections = (Connection*)(base + 0x669B20);
    ServerOptions.identifier = (int*)(base + 0x357FD00);
    accounts = (Account*)(base + 0x357FD08);
    vehicleTypes = (VehicleType*)(base + 0x4D03560);
    events = (Event*)(base + 0x5EDCD80);
    items = (Item*)(base + 0x8117920);
    voices = (Voice*)(base + 0xAEBED80);
    humans = (Human*)(base + 0xCEFE1C8);
    GameOptions.sunTime = (unsigned int*)(base + 0xDFB21E0);
    ServerOptions.numTrafficCars = (unsigned int*)(base + 0x15B253F8);
    players = (Player*)(base + 0x15B35420);
    ServerOptions.serverPort = (unsigned int*)(base + 0x18DB02A0);
    ServerOptions.serverMaxBytesPerSecond = (int*)(base + 0x18DB02A4);
    ServerOptions.adminPassword = (char*)(base + 0x18DB06AC);
    ServerOptions.password = (char*)(base + 0x18DB08AC);
    vehicles = (Vehicle*)(base + 0x1CF42740);
    bonds = (Bond*)(base + 0x24ADC1C0);
    ServerOptions.serverName = (char*)(base + 0x250EC1D4);
    ServerOptions.isPassworded = (int*)(base + 0x250EC5F0);
    ServerOptions.maxPlayers = (int*)(base + 0x250EC5F4);
    ServerOptions.serverSocketEnabled = (int*)(base + 0x39075C24);
    ServerOptions.packetSize = (int*)(base + 0x39075C7C);
    GameOptions.packet = (unsigned char*)(base + 0x39075C84);
    GameOptions.isLevelLoaded = (int*)(base + 0x39496120);
    ServerOptions.loadedMapName = (char*)(base + 0x39496124);
    GameOptions.numStreetIntersections = (unsigned int*)(base + 0x3949617C);
    streetIntersections = (StreetIntersection*)(base + 0x39496184);
    GameOptions.numStreets = (unsigned int*)(base + 0x394B8184);
    streets = (Street*)(base + 0x394B8188);
    GameOptions.numBuildings = (unsigned int*)(base + 0x3958A314);
    buildings = (Building*)(base + 0x3958A358);
    bullets = (Bullet*)(base + 0x44835BC0);
    ServerOptions.gameType = (int*)(base + 0x44ECAACC);
    ServerOptions.mapName = (char*)(base + 0x44ECAAD0);
    GameOptions.RoundweekDay = (int*)(base + 0x44ECACE4);
    GameOptions.roundNumber = (int*)(base + 0x44ECACE8);
    GameOptions.gameState = (int*)(base + 0x44ECACEC);
    GameOptions.gameTimer = (int*)(base + 0x44ECACF4);
    GameOptions.ticksSinceReset = (int*)(base + 0x44ECAD54);
    corporations = (Corporation*)(base + 0x44ECAD80);
    ServerOptions.Round.roundTime = (int*)(base + 0x44F855CC);
    ServerOptions.Round.startCash = (int*)(base + 0x44F855D0);
    ServerOptions.Round.weekly = (unsigned char*)(base + 0x44F855D4);
    ServerOptions.Round.bonusRatio = (unsigned char*)(base + 0x44F855D8);
    ServerOptions.Round.teamDamage = (int*)(base + 0x44F855DC);
    ServerOptions.World.traffic = (int*)(base + 0x44F855E0);
    ServerOptions.World.Crime.civToCiv = (int*)(base + 0x44F855E4);
    ServerOptions.World.Crime.civToTeam = (int*)(base + 0x44F855E8);
    ServerOptions.World.Crime.teamToCiv = (int*)(base + 0x44F855EC);
    ServerOptions.World.Crime.teamToTeam = (int*)(base + 0x44F855F0);
    ServerOptions.World.Crime.teamToTeamInBase = (int*)(base + 0x44F855F4);
    ServerOptions.World.Crime.noSpawn = (int*)(base + 0x44F85600);
    ServerOptions.World.startCash = (int*)(base + 0x44F85608);
    ServerOptions.World.minCash = (int*)(base + 0x44F8560C);
    ServerOptions.World.showJoinExit = (unsigned char*)(base + 0x44F85610);
    ServerOptions.World.respawnTeam = (unsigned char*)(base + 0x44F85614);
    GameOptions.numBullets = (unsigned int*)(base + 0x45E07380);
    GameOptions.numEvents = (unsigned short*)(base + 0x45E07384);
    GameOptions.numConnections = (unsigned int*)(base + 0x45ED7DA8);
    lineIntersectResult = (LineIntersectResult*)(base + 0x569EF720);
    itemTypes = (ItemType*)(base + 0x5A60D7C0);
    trafficCars = (TrafficCar*)(base + 0x5A80BEA0);
}