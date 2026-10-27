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

#ifndef ROSEAPI_H
#define ROSEAPI_H

#define ROSEAPI __attribute__((visibility("default")))

typedef struct {
    float x;
    float y;
    float z;
} Vector;

typedef struct {
    Vector xaxis;
    Vector yaxis;
    Vector zaxis;
} RotMatrix;

typedef struct {
    int active;
    int type;
    int settled;
    int linkedHumanOrItemID;
    int linkedBoneID;
    float mass;
    Vector pos;
    Vector vel;
    Vector startVel;
    RotMatrix rot;
    RotMatrix rotVel;
    Vector scale;
    Vector scaleReciprocal;
    float smallestScaleFactor;
    char __unkpad70[28];
} RigidBody;

typedef struct {
    int active;
    int playerID;
    int humanID;
    int receivingItemID;
    int transmittingItemID;
    int __unk2;
    int __unk3;
    int __unk4;
    float distance;
    float volume;
} EarShot;

typedef struct {
    unsigned int address;
    unsigned int port;
    int unusedConnectionFilter;
    int __unk0;
    int roundNumber;
    int adminVisible;
    int playerID;
    int __unk1;
    int bandwidth;
    int timeoutTime;
    char __unkpad0[36];
    int numReceivedEvents;
    char __unkpad1[12];
    EarShot earShots[8];
    char __unkpad2[0];
    int spectatingHumanID;
    char __unkpad3[130048];
    Vector cameraPosition;
    char __unkpad4[58420];
} Connection;

typedef struct {
    int token_unused;
    int token2_unused;
    int subRosaID;
    int phoneNumber;
    long long steamID;
    char name[32];
    int nameChangeDelay_unused;
    int money;
    int corporateRating;
    int criminalRating;
    int spawnTimer;
    int playTime;
    int bestRaceLapTime;
    int eyeColor_unused;
    int hairColor_unused;
    int skinColor_unused;
    char __unkpad5[8];
    int banTime;
    int isAdmin;
} Account;

typedef struct {
    int usesExternalModel;
    int __unk0;
    int controllableState;
    char __unkpad50[8];
    char name[32];
    int price;
    float mass;
    char __unkpad51[96312];
    float acceleration;
    int numWheels;
    char __unkpad52[3256];
    Vector carBodyOffset;
    char __unkpad53[128];
} VehicleType;

typedef struct {
    int type;
    int tickCreated;
    Vector vectorA;
    Vector vectorB;
    int a;
    int b;
    int c;
    int d;
    float floatA;
    float floatB;
    int __unk0;
    int __unk1;
    char message[64];
} Event;

typedef struct {
    int active;
    int physicsSim;
    int physicsSettled;
    int physicsSettledTimer;
    int isStatic;
    int type;
    float mass;
    int despawnTime;
    int grenadePrimerID;
    int parentHumanID;
    int parentItemID;
    int parentSlot;
    int isInPocket;
    int numChildItems;
    int childItemIDs[8];
    int bodyID;
    Vector pos;
    Vector pos2;
    Vector vel;
    Vector vel2;
    Vector vel3;
    Vector vel4;
    RotMatrix rot;
    char __unkpad39[60];
    Vector boundingBoxCornerA;
    Vector boundingBoxCornerB;
    char __unkpad40[28];
    int health;
    int cooldown;
    int __unk3;
    int bullets;
    char __unkpad41[4];
    int triggerTicks;
    int inputFlags;
    int lastInputFlags;
    char __unkpad42[4];
    int connectedPhoneID;
    int phoneNumber;
    int callerRingTimer;
    int displayPhoneNumber;
    int enteredPhoneNumber;
    char __unkpad43[264];
    int phoneTexture;
    int phoneStatus;
    int vehicleID;
    char __unkpad44[28];
    int cashSpread;
    int cashBillAmount;
    int cashPureValue;
    char __unkpad45[188];
    union {
        unsigned int computerCurrentLine;
        unsigned int memoText;
        int team;
    };
    unsigned int computerTopLine;
    int computerCursor;
    char computerLines[32][64];
    char __unkpad46[0];
    unsigned char computerLineColors[32][64];
    char __unkpad47[740];
    int computerTeam;
    int computerState;
    char __unkpad48[4];
    int computerMissionConnectTimer;
    int computerMissionSubMenu;
    char __unkpad49[1300];
} Item;

typedef struct {
    int isSilenced;
    int __unk0;
    int volumeLevel;
    int currentFrame;
    int __unk1;
    int frameVolumeLevels[64];
    int frameSizes[64];
    unsigned char frames[64][2048];
} Voice;

typedef struct {
    int bodyID;
    Vector pos;
    Vector pos2;
    Vector vel;
    int __unk0;
    int __unk1;
    int __unk2;
    RotMatrix rot;
    char __unkpad20[44];
    float mass;
    Vector scaleReciprocal;
    Vector scale;
    char __unkpad21[152];
} Bone;

typedef struct {
    int count;
    int primaryItemID;
    int secondaryItemID;
    char __unkpad22[28];
} InventorySlot;

typedef struct {
    int active;
    int physicsSim;
    int playerID;
    int accountID;
    int __unk1;
    int __unk2;
    int burgerEatCooldown;
    int stamina;
    int maxStamina;
    int __unk4;
    int vehicleID;
    int vehicleSeat;
    int lastVehicleID;
    int lastVehicleCooldown;
    unsigned int despawnTime;
    int oldHealth;
    int isImmortal;
    int __unk10;
    int __unk11;
    int vehicleExitAnimTimer;
    unsigned int spawnProtection;
    int isOnGround;
    int movementState;
    int standingUpAnimTimer;
    int zoomLevel;
    int __unk14;
    int __unk15;
    int __unk16;
    float throwPitch;
    int __unk18;
    int damage;
    int isStanding;
    Vector pos;
    Vector pos2;
    float viewYaw;
    float viewPitch;
    char __unkpad23[56];
    float viewYaw2;
    char __unkpad24[60];
    float crouchHeight;
    char __unkpad25[12];
    float gearX;
    float strafeInput;
    float gearY;
    float walkInput;
    float viewYawVel;
    float viewPitch2;
    char __unkpad26[212];
    unsigned int inputFlags;
    unsigned int lastInputFlags;
    char __unkpad27[4];
    Bone bones[16];
    char __unkpad28[21808];
    InventorySlot inventorySlots[6];
    char __unkpad29[400];
    int health;
    int bloodLevel;
    int isBleeding;
    int chestHP;
    int __unk27;
    int headHP;
    int __unk28;
    int leftArmHP;
    int __unk29;
    int rightArmHP;
    int __unk30;
    int leftLegHP;
    int __unk31;
    int rightLegHP;
    char __unkpad30[84];
    int progressBar;
    int inventoryAnimationFlags;
    float inventoryAnimationProgress;
    int inventoryAnimationDuration;
    int inventoryAnimationHand;
    int inventoryAnimationSlot;
    int inventoryAnimationCounterFinished;
    int inventoryAnimationCounter;
    char __unkpad31[388];
    int gender;
    int head;
    int skinColor;
    int hairColor;
    int hair;
    int eyeColor;
    int model;
    int suitColor;
    int tieColor;
    int sunglasses;
    int necklace;
    int lastUpdatedWantedGroup;
    char __unkpad32[72];
} Human;

typedef struct {
    int id;
    char text[64];
    int __unk;
} MenuButton;

typedef struct {
    int type;
    int a;
    int b;
    int c;
    int d;
    char text[64];
} Action;

typedef struct {
    int active;
    char name[32];
    int token_unused;
    int token2_unused;
    unsigned int subRosaID;
    unsigned int phoneNumber;
    int isAdmin;
    unsigned int adminAttempts;
    unsigned int accountID;
    int chatDelay;
    char __unkpad6[4];
    int isReady;
    int money;
    int teamMoney;
    int budget;
    int corporateRating;
    int criminalRating;
    int isGodMode;
    int __unk3;
    int itemsBought;
    int vehiclesBought;
    int withdrawnBills;
    char __unkpad7[16];
    unsigned int team;
    unsigned int teamSwitchTimer;
    int stocks;
    int isRoundManager;
    int __unk6;
    int spawnTimer;
    int humanID;
    float gearX;
    float leftRightInput;
    float gearY;
    float forwardBackInput;
    float viewYawDelta;
    float viewPitch;
    float freeLookYaw;
    float freeLookPitch;
    float viewYaw;
    char __unkpad8[32];
    float viewPitchDelta;
    char __unkpad9[56];
    unsigned int inputFlags;
    unsigned int lastInputFlags;
    char __unkpad10[12];
    int zoomLevel;
    char __unkpad11[32];
    int inputType;
    int lastInputType;
    char __unkpad12[4];
    int menuTab;
    int menuTabBuildingID;
    char __unkpad13[72];
    int numActions;
    int lastNumActions;
    char __unkpad14[12];
    Action actions[64];
    char __unkpad15[1100];
    int numMenuButtons;
    MenuButton menuButtons[32];
    char __unkpad16[2304];
    int isBot;
    int isZombie;
    char __unkpad17[24];
    int botHasDestination;
    Vector botDestination;
    char __unkpad18[2660];
    int gender;
    int skinColor;
    int hairColor;
    int hair;
    int eyeColor;
    int model;
    int suitColor;
    int tieColor;
    int sunglasses;
    int head;
    int necklace;
    char __unkpad19[92];
} Player;

typedef struct {
    int bodyID;
    int __unk0;
    int isPopped;
    char __unkpad54[4];
    int health;
    char __unkpad55[28];
    float mass;
    float size;
    char __unkpad56[8];
    float spin;
    char __unkpad57[44];
    float visualHeight;
    char __unkpad58[12];
    float vehicleHeight;
    float skid;
    char __unkpad59[36];
} Wheel;

typedef struct {
    int active;
    unsigned int type;
    int controllableState;
    int health;
    int __unk1;
    int lastDriverPlayerID;
    unsigned int color;
    short despawnTime;
    short spawnedState;
    int isLocked;
    int __unk3;
    int bodyID;
    Vector pos;
    Vector pos2;
    RotMatrix rot;
    int __unk4;
    Vector vel;
    char __unkpad60[10116];
    int windowStates[8];
    char __unkpad61[3556];
    float gearX;
    float steerControl;
    float gearY;
    float gasControl;
    char __unkpad62[56];
    int trafficCarID;
    char __unkpad63[596];
    float acceleration;
    char __unkpad64[140];
    int engineRPM;
    char __unkpad65[12];
    int numWheels;
    Wheel wheels[6];
    char __unkpad66[4700];
    int bladeBodyID;
    char __unkpad67[304];
    int numSeats;
    char __unkpad68[136];
} Vehicle;

typedef struct {
    int active;
    int type;
    int __unk0;
    int despawnTime;
    char __unkpad71[28];
    Vector globalPos;
    Vector localPos;
    Vector otherLocalPos;
    char __unkpad72[72];
    int bodyID;
    int otherBodyID;
    char __unkpad73[84];
} Bond;

typedef struct {
    int __unk0[3];
    Vector pos;
    int streetEast;
    int streetSouth;
    int streetWest;
    int streetNorth;
    char __unkpad75[28];
    int lightsState;
    int lightsTimer;
    int lightsTimerMax;
    int lightEast;
    int lightSouth;
    int lightWest;
    int lightNorth;
    char __unkpad76[40];
} StreetIntersection;

typedef struct {
    int direction;
    Vector posA;
    Vector posB;
} StreetLane;

typedef struct {
    char name[32];
    int __unk0;
    int intersectionA;
    int intersectionB;
    int __unk1[3];
    int numLanes;
    StreetLane lanes[16];
    float __unk2[6];
    Vector trafficCuboidA;
    Vector trafficCuboidB;
    int numTraffic;
    char __unkpad74[1024];
} Street;

typedef struct {
    int type;
    int price;
    int color;
} ShopCar;

typedef struct {
    int type;
    int __unk0[3];
    Vector pos;
    RotMatrix spawnRot;
    Vector interiorCuboidA;
    Vector interiorCuboidB;
    char __unkpad80[51612];
    int numShopCars;
    ShopCar shopCars[16];
    int shopCarSales;
    char __unkpad81[4176];
} Building;

typedef struct {
    unsigned int type;
    int time;
    int playerID;
    float __unk0;
    float __unk1;
    Vector lastPos;
    Vector pos;
    Vector vel;
    char __unkpad69[36];
} Bullet;

typedef struct {
    int active;
    char __unkpad82[8];
    int type;
    int itemID;
    char __unkpad83[8];
    int team1ID;
    int team2ID;
    char __unkpad84[24];
    int diskTypeID;
    int value;
    unsigned int sunTime;
    int location;
    int providedCash;
    char __unkpad85[1036];
} Mission;

typedef struct {
    Vector interiorCuboidA;
    Vector interiorCuboidB;
    Vector vaultCuboidA;
    Vector vaultCuboidB;
    float tableOrientation;
    Vector tableLocation;
    Vector spawnLocation;
    char __unkpad86[8];
    int players;
    char __unkpad87[8];
    int isDoorOpen;
    int managerPlayerID;
    char __unkpad88[276];
    Vector doorPos;
    char __unkpad89[20];
    Mission missions[16];
    char __unkpad90[1124];
    Vector carSpawn1;
    RotMatrix __unk0;
    char __unkpad91[4052];
} Corporation;

typedef struct {
    Vector pos;
    Vector normal;
    float fraction;
    float __unk0;
    int __unk1;
    int __unk2;
    int __unk3;
    int __unk4;
    int vehicleFace;
    int humanBone;
    int __unk6;
    int __unk7;
    int __unk8;
    int __unk9;
    int __unk10;
    int __unk11;
    int __unk12;
    int areaId;
    int blockX;
    int blockY;
    int blockZ;
    int __unk17;
    int __unk18;
    int matMaybe;
    int __unk20;
    int __unk21;
    int __unk22;
    int __unk23;
    int __unk24;
    int __unk25;
    int __unk26;
    int __unk27;
} LineIntersectResult;

typedef struct {
    int __unk0;
    int price;
    float mass;
    int canCollide;
    int isGun;
    int isOneHanded;
    int fireRate;
    int bulletType;
    int __unk2;
    int magazineAmmo;
    float bulletVelocity;
    float bulletSpread;
    char name[64];
    char __unkpad33[12];
    int numHands;
    Vector rightHandPos;
    Vector leftHandPos;
    char __unkpad34[24];
    Vector primaryGripRotAxis;
    float primaryGripRotation;
    Vector secondaryGripRotAxis;
    float secondaryGripRotation;
    char __unkpad35[52];
    Vector boundsCenter;
    char __unkpad36[12];
    int canMountTo[46];
    char __unkpad37[4544];
    Vector gunHoldingPos;
    char __unkpad38[48];
} ItemType;

typedef struct {
    int type;
    int humanID;
    int vehicleID;
    int state;
    Vector pos;
    Vector vel;
    float yaw;
    RotMatrix rot;
    char __unkpad77[44];
    int isBot;
    int isAggressive;
    char __unkpad78[1364];
    int color;
    char __unkpad79[32];
} TrafficCar;

#endif