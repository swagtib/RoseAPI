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

/*GENERAL*/
typedef void* PluginContext;
#define C_PROLOGUE void plugin_init(PluginContext ctx)
#define ISINRANGE(i, r) ((unsigned int)(i) < (unsigned int)(r))

/*CLI COMMANDS*/
typedef void (*CLICallback)(int argc, char **args);
#define ARGSCLI int argc, char **args
ROSEAPI int addclicommand(PluginContext ctx, const char *name, CLICallback callback);

/*HOOKING*/
enum {
    HOOK_LOGIC,
    HOOK_PHYSICS,
    HOOK_BULLETSIM,
    HOOK_LIMBANIM,
    HOOK_ITEMLINK,
    HOOK_COUNT
};
#define FLAG_HOOK_PRE (1u << 0)
#define FLAG_HOOK_POST (1u << 1)
#define FLAG_HOOK_PRIORITY (1u << 2)

//callback must have same signature as function you are hooking, return type void. for post callbacks, modify the signature to add one last argument that has the same type as the function's return type to inspect the result of the original function call
ROSEAPI int addhook(PluginContext ctx, int h, unsigned int flags, void *callback);

/*LOGGING*/

// logs  a plugin error
ROSEAPI void plugin_error(PluginContext ctx, const char *msg, ...);
// logs plugin
ROSEAPI void plugin_log(PluginContext ctx, const char *msg, ...);

/*FORWARD DECLARATION OF STRUCTURES*/
typedef struct Vector Vector;
typedef struct RotMatrix RotMatrix;
typedef struct RigidBody RigidBody;
typedef struct EarShot EarShot;
typedef struct Connection Connection;
typedef struct Account Account;
typedef struct VehicleType VehicleType;
typedef struct Event Event;
typedef struct Item Item;
typedef struct Voice Voice;
typedef struct Bone Bone;
typedef struct InventorySlot InventorySlot;
typedef struct Human Human;
typedef struct MenuButton MenuButton;
typedef struct Action Action;
typedef struct Player Player;
typedef struct Wheel Wheel;
typedef struct Vehicle Vehicle;
typedef struct Bond Bond;
typedef struct StreetIntersection StreetIntersection;
typedef struct StreetLane StreetLane;
typedef struct Street Street;
typedef struct ShopCar ShopCar;
typedef struct Building Building;
typedef struct Bullet Bullet;
typedef struct Mission Mission;
typedef struct Corporation Corporation;
typedef struct LineIntersectResult LineIntersectResult;
typedef struct ItemType ItemType;
typedef struct TrafficCar TrafficCar;

typedef enum {
    MAX_ACCOUNTS = 32768,
    MAX_PLAYERS = 256,
    MAX_HUMANS = 256,
    MAX_ITEMTYPES = 46,
    MAX_ITEMS = 1024,
    MAX_VEHICLETYPES = 17,
    MAX_VEHICLES = 512,
    MAX_RIGIDBODIES = 8192,
    MAX_BONDS = 16384,
    MAX_CORPS = 32
} MaxNumberOf;

/*SERVER OPTIONS*/
typedef struct {
    float* gravity;
    unsigned int* subVersion;
    unsigned int* version;
    int* identifier;
    unsigned int* numTrafficCars;
    unsigned int* serverPort;
    int* serverMaxBytesPerSecond;
    char* adminPassword;
    char* password;
    char* serverName;
    int* isPassworded;
    int* maxPlayers;
    int* serverSocketEnabled;
    int* packetSize;
    char* loadedMapName;
    int* gameType;
    char* mapName;
    struct {
        int* roundTime;
        int* startCash;
        unsigned char* weekly;
        unsigned char* bonusRatio;
        int* teamDamage;
    } Round;
    struct {
        int* traffic;
        int* startCash;
        int* minCash;
        unsigned char* showJoinExit;
        unsigned char* respawnTeam;
        struct {
            int* civToCiv;
            int* civToTeam;
            int* teamToCiv;
            int* teamToTeam;
            int* teamToTeamInBase;
            int* noSpawn;
        } Crime;
    } World;
} ServerOpt;
extern ROSEAPI ServerOpt ServerOptions;

/*GAME STATUS*/
typedef struct {
    unsigned int* sunTime;
    unsigned char* packet;
    int* isLevelLoaded;
    unsigned int* numStreetIntersections;
    unsigned int* numStreets;
    unsigned int* numBuildings;
    int* RoundweekDay;
    int* roundNumber;
    int* gameState;
    int* gameTimer;
    int* ticksSinceReset;
    unsigned int* numBullets;
    unsigned short* numEvents;
    unsigned int* numConnections;
} GameOpt;
extern ROSEAPI GameOpt GameOptions;

/* FORWARD DECLARATON OF ENUMERATIONS */
typedef enum SoundIndex SoundIndex;
typedef enum ItemTypeIndex ItemTypeIndex;
typedef enum BulletTypeIndex BulletTypeIndex;
typedef enum ComputerColorIndex ComputerColorIndex;
typedef enum VehicleTypeIndex VehicleTypeIndex;
typedef enum VehicleColorIndex VehicleColorIndex;
typedef enum ColorShirtIndex ColorShirtIndex;
typedef enum ColorSuitIndex ColorSuitIndex;
typedef enum ColorTieIndex ColorTieIndex;
typedef enum NecklaceIndex NecklaceIndex;
typedef enum BodyPartIndex BodyPartIndex;
typedef enum MovementStateIndex MovementStateIndex;
typedef enum InputFlagIndex InputFlagIndex;
typedef enum TeamIndex TeamIndex;
typedef enum GameTypeIndex GameTypeIndex;
typedef enum GameStateIndex GameStateIndex;
typedef enum MenuTabIndex MenuTabIndex;
typedef enum MissionLocationIndex MissionLocationIndex;
typedef enum BulletHitTypeIndex BulletHitTypeIndex;
typedef enum MessageTypeIndex MessageTypeIndex;
typedef enum VehicleUpdateIndex VehicleUpdateIndex;
typedef enum DistanceIndex DistanceIndex;

/*GLOBALS*/
extern ROSEAPI RigidBody* bodies;
extern ROSEAPI Connection* connections;
extern ROSEAPI Account* accounts;
extern ROSEAPI VehicleType* vehicleTypes;
extern ROSEAPI Event* events;
extern ROSEAPI Item* items;
extern ROSEAPI Voice* voices;
extern ROSEAPI Human* humans;
extern ROSEAPI Player* players;
extern ROSEAPI Vehicle* vehicles;
extern ROSEAPI Bond* bonds;
extern ROSEAPI StreetIntersection* streetIntersections;
extern ROSEAPI Street* streets;
extern ROSEAPI Building* buildings;
extern ROSEAPI Bullet* bullets;
extern ROSEAPI Corporation* corporations;
extern ROSEAPI LineIntersectResult* lineIntersectResult;
extern ROSEAPI ItemType* itemTypes;
extern ROSEAPI TrafficCar* trafficCars;

/* VECTOR */
ROSEAPI void vectorcopy(Vector* copyto, Vector* copyfrom);
ROSEAPI void vectorzero(Vector* v);
ROSEAPI float vectorlengthsquared(Vector* v);
ROSEAPI void vectorset(Vector* v, float x, float y, float z);
ROSEAPI float vectorlength(Vector* v);
ROSEAPI void vectornormalize(Vector* v);
ROSEAPI int vectorincuboid(Vector* v, Vector* min, Vector* max);
ROSEAPI void vectorscale(Vector* v, float scalar);
ROSEAPI void vectorneg(Vector* v);
ROSEAPI void vectorsub(Vector* v, Vector* sub);
ROSEAPI void vectoradd(Vector* v, Vector* add);
ROSEAPI float vectordot(Vector* a, Vector* b);
ROSEAPI void vectorcross(Vector* result, Vector* a, Vector* b);
ROSEAPI float vectordistancesquared(Vector* a, Vector* b);
ROSEAPI float vectordistance(Vector* a, Vector* b);
ROSEAPI int vectorinsphere(Vector* point, Vector* center, float radius);
ROSEAPI void pitchtorotmatrix(RotMatrix *result, float pitch);
ROSEAPI void yawtorotmatrix(RotMatrix *result, float yaw);
ROSEAPI void rolltorotmatrix(RotMatrix *result, float roll);
ROSEAPI void vectorrotate(Vector *v, RotMatrix *r);
ROSEAPI void rotmatrixmul(RotMatrix* result, RotMatrix* a, RotMatrix* b);
ROSEAPI void eulertorotmatrix(RotMatrix* result, Vector* euler);
ROSEAPI void vectorlerp(Vector* result, Vector *a, Vector *b, float t);
ROSEAPI int vectorequals(Vector* a, Vector* b, float epsilon);
ROSEAPI void vectorsetlength(Vector* v, float length);
ROSEAPI void rotmatrixtranspose(RotMatrix* result, RotMatrix* m);
ROSEAPI void vectorrotateinverse(Vector *vec, RotMatrix *m);
ROSEAPI void rotmatrixtoeuler(Vector* result, RotMatrix* r);

/* API */

//creates a human with playerid p, returns an index >= 0 or -1 on failure
ROSEAPI int humancreate(Vector* pos, RotMatrix* rot, int p);
//creates an item, returns an index >= 0 or -1 on failure
ROSEAPI int itemcreate(ItemTypeIndex t, Vector* pos, Vector* vel, RotMatrix* rot);
//creates a vehicle, returns an index >= 0 or -1 on fail
ROSEAPI int vehiclecreate(VehicleTypeIndex vt, Vector* pos, Vector* vel, RotMatrix* rot, VehicleColorIndex c);
// returns index >= 0 or -1 on fail
ROSEAPI int playercreate(void);
// deletes player p
ROSEAPI void playerdelete(int p);
// deletes human h
ROSEAPI void humandelete(int h);
// delete item i
ROSEAPI void itemdelete(int i);
//deletes vehicle v
ROSEAPI void vehicledelete(int v);
//applies damage to bone of human h
ROSEAPI void humanapplydamage(int h, int bone, int damage);
//applies damage d to vehicle v
ROSEAPI void vehicleapplydamage(int v, int d);
//links child to item or item to human, returns falsy value on fail & truthy on success
ROSEAPI int itemlink(int item, int child, int human, int slot);
// arms human with weapon & mag count
ROSEAPI void scenarioarmhuman(int human, int weapon, int magc);
//creates a bullet at pos with velocity vel with owner item
ROSEAPI void eventcreatebullet(BulletTypeIndex bt, Vector* pos, Vector* vel, int item);
//creates a bullet hit effect
ROSEAPI void eventcreatebullethit(BulletHitTypeIndex ht, Vector* pos, Vector* normal);
//creates a message event, msg cannot exceed 63 (char 64 reserved as null terminator)
ROSEAPI void eventcreatemessage(MessageTypeIndex mt, char* msg, int speaker, DistanceIndex dist);
// updates the vehicle type of v
ROSEAPI void eventupdatevehicletype(int v);
// updates vehicle v
ROSEAPI void eventupdatevehicle(int v, VehicleUpdateIndex ut, int part, Vector* pos, Vector* hitvel);
// updates item i
ROSEAPI void eventupdateitem(int i);
//updates p's information or finance depending on finance's truthy value
ROSEAPI void eventupdateplayer(int p, int finance);
//creates a sound
ROSEAPI void eventcreatesound(SoundIndex s, Vector* pos, float vol, float pitch);
//creates a sound that follows item itm
ROSEAPI void eventcreateitemsound(SoundIndex s, int itm, float vol, float pitch);
//updates corp c with data stored in opaque, if dm == 0 it updates door state with state = opaque, if dm != 0 it updates mission state with state = opaque
ROSEAPI void eventupdatecorp(int c, int opaque, int dm);
//updates eliminator
ROSEAPI void eventupdateelim(int player, int tracker, int team, int savior, Vector* saviorpos);
//creates an explosion effect & sound
ROSEAPI void eventcreateexplosion(Vector* pos);
//checks for a line intersection with triangle defined by tri#
ROSEAPI int lineintersecttriangle(Vector* out, Vector* normal, float* outfraction, Vector* posa, Vector* posb, Vector* tria, Vector* trib, Vector* tric);
//checks for a line intersection with human h
ROSEAPI int lineintersecthuman(int h, Vector* posa, Vector* posb, float pad);
// checks for a line intersection with vehicle v
ROSEAPI int lineintersectvehicle(int v, Vector* posa, Vector* posb, int wheels);
//checks for a line intersection with the level
ROSEAPI int lineintersectlevel(Vector* posa, Vector* posb, int cityobjects);
//gives player p a wanted value
ROSEAPI void playergivewanted(int p, int victim, int base);
ROSEAPI int itemgetbillval(int i);
ROSEAPI int itemaddbill(int i, int pos, int amount);
ROSEAPI void itemremovebill(int i, int amount);
//maximum of 1023 char (1024 reserved null terminator)
ROSEAPI int itemsetmemotext(int i, char* text);
//networks line on computer i
ROSEAPI int itemnetworkcomputerline(int i, unsigned int line);

/* STRUCTURES */
struct Vector {
    float x;
    float y;
    float z;
};

struct RotMatrix {
    Vector xaxis;
    Vector yaxis;
    Vector zaxis;
};

struct RigidBody {
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
};

struct EarShot {
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
};

struct Connection {
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
};

struct Account {
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
};

struct VehicleType {
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
};

struct Event {
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
};

struct Item {
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
        unsigned int __memoText;
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
};

struct Voice {
    int isSilenced;
    int __unk0;
    int volumeLevel;
    int currentFrame;
    int __unk1;
    int frameVolumeLevels[64];
    int frameSizes[64];
    unsigned char frames[64][2048];
};

struct Bone {
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
};

struct InventorySlot {
    int count;
    int primaryItemID;
    int secondaryItemID;
    char __unkpad22[28];
};

struct Human {
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
};

struct MenuButton {
    int id;
    char text[64];
    int __unk;
};

struct Action {
    int type;
    int a;
    int b;
    int c;
    int d;
    char text[64];
};

struct Player {
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
};

struct Wheel {
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
};

struct Vehicle {
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
};

struct Bond {
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
};

struct StreetIntersection {
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
};

struct StreetLane {
    int direction;
    Vector posA;
    Vector posB;
};

struct Street {
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
};

struct ShopCar {
    int type;
    int price;
    int color;
};

struct Building {
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
};

struct Bullet {
    unsigned int type;
    int time;
    int playerID;
    float __unk0;
    float __unk1;
    Vector lastPos;
    Vector pos;
    Vector vel;
    char __unkpad69[36];
};

struct Mission {
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
};

struct Corporation {
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
};

struct LineIntersectResult {
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
};

struct ItemType {
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
};

struct TrafficCar {
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
};

/* ENUMS */

enum SoundIndex {
    SOUND_CAR_ENGINE = 8,
    SOUND_TIRE_DRIFT = 10,
    SOUND_RICOCHET1 = 11,
    SOUND_RICOCHET2 = 12,
    SOUND_RICOCHET3 = 13,
    SOUND_RICOCHET4 = 14,
    SOUND_RICOCHET5 = 15,
    SOUND_RICOCHET6 = 16,
    SOUND_RICOCHET7 = 17,
    SOUND_RICOCHET8 = 18,
    SOUND_CAR_CRASH1 = 19,
    SOUND_CAR_CRASH2 = 20,
    SOUND_BULLET_HIT_BODY1 = 21,
    SOUND_BULLET_HIT_BODY2 = 22,
    SOUND_BULLET_HIT_METAL1 = 23,
    SOUND_BULLET_HIT_METAL2 = 24,
    SOUND_GLASS_BREAK = 25,
    SOUND_PHONE_RING = 27,
    SOUND_PHONE_BUTTON0 = 28,
    SOUND_PHONE_BUTTON1 = 29,
    SOUND_PHONE_BUTTON2 = 30,
    SOUND_PHONE_BUTTON3 = 31,
    SOUND_PHONE_BUTTON4 = 32,
    SOUND_PHONE_BUTTON5 = 33,
    SOUND_PHONE_BUTTON6 = 34,
    SOUND_PHONE_BUTTON7 = 35,
    SOUND_PHONE_BUTTON8 = 36,
    SOUND_PHONE_BUTTON9 = 37,
    SOUND_PHONE_BUSY_SIGNAL = 38,
    SOUND_MAGAZINE_LOAD = 39,
    SOUND_BULLET_SHELL_BOUNCE = 40,
    SOUND_GEAR_SHIFT = 41,
    SOUND_HELICOPTER = 42,
    SOUND_TRAIN1 = 43,
    SOUND_TRAIN2 = 44,
    SOUND_TRAIN3 = 45,
    SOUND_TRAIN4 = 46,
    SOUND_FACTORY_WHISTLE = 47,
    SOUND_EXPLOSION = 48,
    SOUND_COMPUTER_DIALUP = 49,
    SOUND_COMPUTER_DRIVE = 50,
    SOUND_AK47_FIRE1 = 71,
    SOUND_AK47_FIRE2 = 72,
    SOUND_AK47_FIRE3 = 73,
    SOUND_AK47_FIRE4 = 74,
    SOUND_AK47_FIRE5 = 75,
    SOUND_AK47_FIRE6 = 76,
    SOUND_M16_FIRE1 = 77,
    SOUND_M16_FIRE2 = 78,
    SOUND_M16_FIRE3 = 79,
    SOUND_M16_FIRE4 = 80,
    SOUND_M16_FIRE5 = 81,
    SOUND_M16_FIRE6 = 82,
    SOUND_MP5_FIRE1 = 83,
    SOUND_MP5_FIRE2 = 84,
    SOUND_MP5_FIRE3 = 85,
    SOUND_MP5_FIRE4 = 86,
    SOUND_MP5_FIRE5 = 87,
    SOUND_MP5_FIRE6 = 88,
    SOUND_UZI_FIRE1 = 89,
    SOUND_UZI_FIRE2 = 90,
    SOUND_UZI_FIRE3 = 91,
    SOUND_UZI_FIRE4 = 92,
    SOUND_UZI_FIRE5 = 93,
    SOUND_UZI_FIRE6 = 94,
    SOUND_9MM_FIRE1 = 95,
    SOUND_9MM_FIRE2 = 96,
    SOUND_9MM_FIRE3 = 97,
    SOUND_9MM_FIRE4 = 98,
    SOUND_9MM_FIRE5 = 99,
    SOUND_9MM_FIRE6 = 100,
    SOUND_COUNT
};

enum ItemTypeIndex {
    ITEMTYPE_AUTO5,
    ITEMTYPE_AK47,
    ITEMTYPE_AK47_MAGAZINE,
    ITEMTYPE_M16,
    ITEMTYPE_M16_MAGAZINE,
    ITEMTYPE_MAGNUM,
    ITEMTYPE_45_BULLETS,
    ITEMTYPE_MP5,
    ITEMTYPE_MP5_MAGAZINE,
    ITEMTYPE_UZI,
    ITEMTYPE_UZI_MAGAZINE,
    ITEMTYPE_9MM,
    ITEMTYPE_9MM_MAGAZINE,
    ITEMTYPE_GRENADE,
    ITEMTYPE_BANDAGE,
    ITEMTYPE_BRIEFCASE,
    ITEMTYPE_OPEN_BRIEFCASE,
    ITEMTYPE_CASH_ROUND,
    ITEMTYPE_CASH_WORLD,
    ITEMTYPE_BLACK_DISK,
    ITEMTYPE_GREEN_DISK,
    ITEMTYPE_BLUE_DISK,
    ITEMTYPE_WHITE_DISK,
    ITEMTYPE_GOLD_DISK,
    ITEMTYPE_RED_DISK,
    ITEMTYPE_CELL_PHONE,
    ITEMTYPE_WALKIE_TALKIE,
    ITEMTYPE_KEY,
    ITEMTYPE_DOOR,
    ITEMTYPE_NEWSPAPER,
    ITEMTYPE_BURGER,
    ITEMTYPE_DESK_BROKEN,
    ITEMTYPE_LAMP_BROKEN,
    ITEMTYPE_PAY_PHONE,
    ITEMTYPE_MEMO,
    ITEMTYPE_SOCCER_BALL,
    ITEMTYPE_ROPE,
    ITEMTYPE_BOX,
    ITEMTYPE_BIG_BOX,
    ITEMTYPE_COMPUTER,
    ITEMTYPE_ARCADE,
    ITEMTYPE_TABLE,
    ITEMTYPE_TABLETEST2,
    ITEMTYPE_CUBEWALL,
    ITEMTYPE_BOTTLE,
    ITEMTYPE_WATERMELON,
    ITEMTYPE_COUNT
};

enum BulletTypeIndex {
    BULLETTYPE_AK47,
    BULLETTYPE_M16,
    BULLETTYPE_9MM,
    BULLETTYPE_MAGNUM,
    BULLETTYPE_COUNT
};

enum ComputerColorIndex {
    COMPUTERCOLOR_BLACK,
    COMPUTERCOLOR_BLUE,
    COMPUTERCOLOR_GREEN,
    COMPUTERCOLOR_CYAN,
    COMPUTERCOLOR_RED,
    COMPUTERCOLOR_MAGENTA,
    COMPUTERCOLOR_BROWN,
    COMPUTERCOLOR_LIGHT_GRAY,
    COMPUTERCOLOR_DARK_GRAY,
    COMPUTERCOLOR_LIGHT_BLUE,
    COMPUTERCOLOR_LIGHT_GREEN,
    COMPUTERCOLOR_LIGHT_CYAN,
    COMPUTERCOLOR_LIGHT_RED,
    COMPUTERCOLOR_LIGHT_MAGENTA,
    COMPUTERCOLOR_YELLOW,
    COMPUTERCOLOR_WHITE,
    COMPUTERCOLOR_COUNT
};

enum VehicleTypeIndex {
    VEHICLETYPE_TOWN_CAR,
    VEHICLETYPE_TOWN_CAR_2,
    VEHICLETYPE_METRO,
    VEHICLETYPE_LIMO,
    VEHICLETYPE_TURBO,
    VEHICLETYPE_TURBO_S,
    VEHICLETYPE_BEAMER,
    VEHICLETYPE_VAN,
    VEHICLETYPE_VAN2,
    VEHICLETYPE_MINIVAN,
    VEHICLETYPE_TRUCK,
    VEHICLETYPE_TRAILER,
    VEHICLETYPE_HELICOPTER,
    VEHICLETYPE_TRAIN,
    VEHICLETYPE_NO_CLIP,
    VEHICLETYPE_HATCHBACK,
    VEHICLETYPE_TEST,
    VEHICLETYPE_COUNT
};

enum VehicleColorIndex {
    VEHICLECOLOR_BLACK,
    VEHICLECOLOR_RED,
    VEHICLECOLOR_BLUE,
    VEHICLECOLOR_GREY,
    VEHICLECOLOR_WHITE,
    VEHICLECOLOR_GOLDEN,
    VEHICLECOLOR_BROKEN,
    VEHICLECOLOR_COUNT
};

enum ColorShirtIndex {
    COLOR_SHIRT_WHITE,
    COLOR_SHIRT_PINK,
    COLOR_SHIRT_YELLOW,
    COLOR_SHIRT_GREEN,
    COLOR_SHIRT_CYAN,
    COLOR_SHIRT_RED,
    COLOR_SHIRT_WHITE_2,
    COLOR_SHIRT_WHITE_3,
    COLOR_SHIRT_RED_2,
    COLOR_SHIRT_BLACK,
    COLOR_SHIRT_BLUE,
    COLOR_SHIRT_GREEN_2,
    COLOR_SHIRT_WHITE_4,
    COLOR_SHIRT_WHITE_5,
    COLOR_SHIRT_WHITE_6,
    COLOR_SHIRT_WHITE_7,
    COLOR_SHIRT_COUNT
};

enum ColorSuitIndex {
    COLOR_SUIT_BROWN,
    COLOR_SUIT_BLACK,
    COLOR_SUIT_LIGHT_GRAY,
    COLOR_SUIT_TURQUOISE,
    COLOR_SUIT_GREEN,
    COLOR_SUIT_PINK,
    COLOR_SUIT_GOLD,
    COLOR_SUIT_WHITE,
    COLOR_SUIT_RED,
    COLOR_SUIT_BLUE,
    COLOR_SUIT_DARK_BLUE,
    COLOR_SUIT_GRAY,
    COLOR_SUIT_WHITE_2,
    COLOR_SUIT_WHITE_3,
    COLOR_SUIT_WHITE_4,
    COLOR_SUIT_WHITE_5,
    COLOR_SUIT_COUNT
};

enum ColorTieIndex {
    COLOR_TIE_NONE,
    COLOR_TIE_GREEN,
    COLOR_TIE_GOLD,
    COLOR_TIE_RED,
    COLOR_TIE_PINK,
    COLOR_TIE_DARK_RED,
    COLOR_TIE_WHITE,
    COLOR_TIE_LIGHT_GRAY,
    COLOR_TIE_BLACK,
    COLOR_TIE_CYAN,
    COLOR_TIE_PURPLE,
    COLOR_TIE_WHITE_2,
    COLOR_TIE_WHITE_3,
    COLOR_TIE_WHITE_4,
    COLOR_TIE_WHITE_5,
    COLOR_TIE_WHITE_6,
    COLOR_TIE_COUNT
};

enum NecklaceIndex {
    NECKLACE_NONE,
    NECKLACE_JEWEL,
    NECKLACE_DOLLAR,
    NECKLACE_COUNT
};

enum BodyPartIndex {
    BODYPART_PELVIS,
    BODYPART_STOMACH,
    BODYPART_TORSO,
    BODYPART_HEAD,
    BODYPART_LEFT_SHOULDER,
    BODYPART_LEFT_FOREARM,
    BODYPART_LEFT_HAND,
    BODYPART_RIGHT_SHOULDER,
    BODYPART_RIGHT_FOREARM,
    BODYPART_RIGHT_HAND,
    BODYPART_LEFT_THIGH,
    BODYPART_LEFT_SHIN,
    BODYPART_LEFT_FOOT,
    BODYPART_RIGHT_THIGH,
    BODYPART_RIGHT_SHIN,
    BODYPART_RIGHT_FOOT,
    BODYPART_COUNT
};

enum MovementStateIndex {
    MOVEMENTSTATE_STANDING,
    MOVEMENTSTATE_MID_AIR,
    MOVEMENTSTATE_SLIDING,
    MOVEMENTSTATE_FLOATING,
    MOVEMENTSTATE_INSIDE_OF_VEHICLE,
    MOVEMENTSTATE_LAYING_ON_GROUND,
    MOVEMENTSTATE_STRAIGHTENED_OUT_LEGS,
    MOVEMENTSTATE_COUNT
};

enum InputFlagIndex {
    INPUTFLAG_NOTHING,
    INPUTFLAG_LEFT_MOUSE = (1U << 0),
    INPUTFLAG_RIGHT_MOUSE = (1U << 1),
    INPUTFLAG_SPACE = (1U << 2),
    INPUTFLAG_CTRL = (1U << 3),
    INPUTFLAG_SHIFT = (1U << 4),
    INPUTFLAG_Q = (1U << 5),
    INPUTFLAG_E = (1U << 11),
    INPUTFLAG_R = (1U << 12),
    INPUTFLAG_F = (1U << 13),
    INPUTFLAG_DELETE = (1U << 18),
    INPUTFLAG_Z = (1U << 19)
};

enum TeamIndex {
    TEAM_GOLDMEN,
    TEAM_MONSOTA,
    TEAM_OXS,
    TEAM_NEXACO,
    TEAM_PENTACOM,
    TEAM_PRODOCON,
    TEAM_MEGACORP,
    TEAM_7,
    TEAM_8,
    TEAM_9,
    TEAM_10,
    TEAM_11,
    TEAM_12,
    TEAM_13,
    TEAM_14,
    TEAM_15,
    TEAM_16,
    TEAM_CIV,
    TEAM_COUNT
};

enum GameTypeIndex {
    GAMETYPE_PRACTICE,
    GAMETYPE_DRIVING,
    GAMETYPE_RACING,
    GAMETYPE_ROUND,
    GAMETYPE_WORLD,
    GAMETYPE_ELIMINATOR,
    GAMETYPE_COOPERATIVE,
    GAMETYPE_VERSUS,
    GAMETYPE_NONE,
    GAMETYPE_COUNT
};

enum GameStateIndex {
    GAMESTATE_IDLE,
    GAMESTATE_INTERMISSION,
    GAMESTATE_GAME,
    GAMESTATE_RESTARTING,
    GAMESTATE_PAUSED,
    GAMESTATE_COUNT
};

enum MenuTabIndex {
    MENUTAB_NOTHING = 0,
    MENUTAB_ENTER_CITY = 1,
    MENUTAB_LOBBY = 2,
    MENUTAB_EMPTY_BASE_MENU = 3,
    MENUTAB_WORLD_CAR_SHOP = 9,
    MENUTAB_WORLD_GUN_STORE_BURGER_SHOP_CLOTHING_STORE = 10,
    MENUTAB_WORLD_STORE = 11,
    MENUTAB_WORLD_BANK = 12,
    MENUTAB_WORLD_BANK_2 = 13,
    MENUTAB_ROUND_CORP_WEAPONS_MENU = 14,
    MENUTAB_ROUND_CORP_AMMO_MENU = 15,
    MENUTAB_ROUND_CORP_EQUIPMENT_MENU = 16,
    MENUTAB_ROUND_CORP_VEHICLE_MENU = 17,
    MENUTAB_ROUND_CORP_STOCK_MENU = 18,
    MENUTAB_WORLD_EMPTY_CORP_MENU = 19,
    MENUTAB_WORLD_CORP_APPLICATION_MENU = 20,
    MENUTAB_WORLD_CORP_HIRING_MENU = 22,
    MENUTAB_WORLD_CORP_FIRING_MENU = 23,
    MENUTAB_WORLD_CORP_TEAM_MENU = 24,
    MENUTAB_WORLD_CORP_REQUISITION_MENU = 25,
    MENUTAB_COUNT
};

enum MissionLocationIndex {
    MISSIONLOCATION_HONDO,
    MISSIONLOCATION_RIO,
    MISSIONLOCATION_BURGER,
    MISSIONLOCATION_KAMEL,
    MISSIONLOCATION_MUSEUM,
    MISSIONLOCATION_MALL,
    MISSIONLOCATION_GAS,
    MISSIONLOCATION_REDCUBE,
    MISSIONLOCATION_COUNT
};

enum BulletHitTypeIndex {
    BULLETHIT_HOLE,
    BULLETHIT_HUMAN,
    BULLETHIT_METAL,
    BULLETHIT_BLEED,
    BULLETHIT_COUNT
};

enum MessageTypeIndex {
    MESSAGETYPE_CHAT,
    MESSAGETYPE_SPEAK,
    MESSAGETYPE_ITEM,
    MESSAGETYPE_MOTD,
    MESSAGETYPE_ADMINS,
    MESSAGETYPE_UNK,
    MESSAGETYPE_CRIM,
    MESSAGETYPE_COUNT
};

enum VehicleUpdateIndex {
    VEHICLEUPDATE_WINDOW,
    VEHICLEUPDATE_TIRE,
    VEHICLEUPDATE_BODY,
    VEHICLEUPDATE_COUNT
};

enum DistanceIndex {
    DISTANCE_WHISPER,
    DISTANCE_NORMAL,
    DISTANCE_YELL,
    DISTANCE_COUNT
};

#endif