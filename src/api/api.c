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

#include "engine.h"
#include <roseapi.h>
#include <string.h>

int humancreate(Vector* pos, RotMatrix* rot, int p)
{
    if (!pos || !rot) return -1;
    if (!ISINRANGE(p, MAX_PLAYERS)) return -1;
    int idx = createHuman_game(pos, rot, p);
    return idx;
}

int itemcreate(ItemTypeIndex t, Vector* pos, Vector* vel, RotMatrix* rot)
{
    if (!pos || !vel || !rot) return -1;
    if (!ISINRANGE(t, ITEMTYPE_COUNT)) return -1; // technically speaking i should be comparing against MAX_ITEMTYPES but this only allows defined IT's to go thru
    int idx = createItem_game(t, pos, vel, rot);
    return idx;
}

int vehiclecreate(VehicleTypeIndex vt, Vector* pos, Vector* vel, RotMatrix* rot, VehicleColorIndex c)
{
    if (!pos || !vel || !rot) return -1;
    if (!ISINRANGE(vt, VEHICLETYPE_COUNT)) return -1; // same thing as itemcreate
    if (!ISINRANGE(c, VEHICLECOLOR_COUNT)) return -1;
    int idx = createVehicle_game(vt, pos, vel, rot, c);
    return idx;
}

int playercreate(void)
{
    return createPlayer_game();
}

void playerdelete(int p)
{
    if (!ISINRANGE(p, MAX_PLAYERS)) return;
    deletePlayer_game(p);
}

void humandelete(int h)
{
    if (!ISINRANGE(h, MAX_HUMANS)) return;
    deleteHuman_game(h);
}

void itemdelete(int i)
{
    if (!ISINRANGE(i, MAX_ITEMS)) return;
    deleteItem_game(i);
}

void vehicledelete(int v)
{
    if (!ISINRANGE(v, MAX_VEHICLES)) return;
    deleteVehicle_game(v);
}

void humanapplydamage(int h, int bone, int damage)
{
    if (!ISINRANGE(h, MAX_HUMANS)) return;
    humanApplyDamage_game(h, bone, 0, damage);
}

void vehicleapplydamage(int v, int d)
{
    if (!ISINRANGE(v, MAX_VEHICLES)) return;
    vehicleApplyDamage_game(v, d);
}

int itemlink(int item, int child, int human, int slot)
{
    if (!ISINRANGE(item, MAX_ITEMS) || !ISINRANGE(child, MAX_ITEMS) || !ISINRANGE(human, MAX_HUMANS)) return -1; // possibly check slot too
    return linkItem_game(item, child, human, slot);
}

void scenarioarmhuman(int human, int weapon, int magc)
{
    if (!ISINRANGE(human, MAX_HUMANS) || !ISINRANGE(weapon, ITEMTYPE_COUNT)) return;
    scenarioArmHuman_game(human, weapon, magc);
}

void eventcreatebullet(BulletTypeIndex bt, Vector* pos, Vector* vel, int item)
{
    if (!pos || !vel) return;
    if (!ISINRANGE(bt, BULLETTYPE_COUNT) || !ISINRANGE(item, MAX_ITEMS)) return;
    createEventBullet_game(bt, pos, vel, item);
}

void eventcreatebullethit(BulletHitTypeIndex ht, Vector* pos, Vector* normal)
{
    if (!pos || !normal) return;
    if (!ISINRANGE(ht, BULLETHIT_COUNT)) return;
    createEventBulletHit_game(0, ht, pos, normal);
}

void eventcreatemessage(MessageTypeIndex mt, char* msg, int speaker, DistanceIndex dist)
{
    if (!ISINRANGE(mt, MESSAGETYPE_COUNT)) return;
    if (!ISINRANGE(dist, DISTANCE_COUNT)) return;
    if (strlen(msg) > 63) return;
    createEventMessage_game(mt, msg, speaker, dist);
}

void eventupdatevehicletype(int v)
{
    if (!ISINRANGE(v, MAX_VEHICLES)) return;
    createEventCreateVehicle_game(v);
}

void eventupdatevehicle(int v, VehicleUpdateIndex ut, int part, Vector* pos, Vector* hitvel)
{
    if (!pos || !hitvel) return;
    if (!ISINRANGE(ut, VEHICLEUPDATE_COUNT)) return;
    if (!ISINRANGE(v, MAX_VEHICLES)) return;
    createEventUpdateVehicle_game(v, ut, part, pos, hitvel);
}

void eventupdateitem(int i)
{
    if (!ISINRANGE(i, MAX_ITEMS)) return;
    createEventUpdateItemInfo_game(i);
}

void eventupdateplayer(int p, int finance)
{
    if (!ISINRANGE(p, MAX_PLAYERS)) return;
    if (finance)
    {
        createEventUpdatePlayerFinance_game(p);
    } else createEventUpdatePlayer_game(p);
}

void eventcreatesound(SoundIndex s, Vector* pos, float vol, float pitch)
{
    if (!pos) return;
    if (!ISINRANGE(s, SOUND_COUNT)) return;
    createEventSound_game(s, pos, vol, pitch);
}

void eventcreateitemsound(SoundIndex s, int itm, float vol, float pitch)
{
    if (!ISINRANGE(s, SOUND_COUNT)) return;
    if (!ISINRANGE(itm, MAX_ITEMS)) return;
    createEventSoundItem_game(s, itm, vol, pitch);
}

void eventupdatecorp(int c, int opaque, int dm)
{
    if (!ISINRANGE(c, MAX_CORPS)) return;
    switch (dm) {
        case 0:
        createEventUpdateCorpDoorState_game(c, opaque);
        break;

        case 1:
        createEventUpdateCorpMission_game(c, opaque);
        break;

        default:
        break;
    }
}

void eventupdateelim(int player, int tracker, int team, int savior, Vector* saviorpos)
{
    if (!saviorpos) return;
    if (!ISINRANGE(player, MAX_PLAYERS) || !ISINRANGE(savior, MAX_PLAYERS) || !ISINRANGE(team, MAX_CORPS)) return;
    createEventUpdateElimState_game(player, tracker, team, savior, saviorpos);
}

void eventcreateexplosion(Vector* pos)
{
    if (!pos) return;
    createEventExplosion_game(0, pos); // afaik there's no other explosion types
}

int lineintersecttriangle(Vector* out, Vector* normal, float* outfraction, Vector* posa, Vector* posb, Vector* tria, Vector* trib, Vector* tric)
{
    if (!out || !normal || !outfraction || !posa || !posb || !tria || !trib || !tric) return -1;
    return lineIntersectTriangle_game(out, normal, outfraction, posa, posb, tria, trib, tric);
}

int lineintersecthuman(int h, Vector* posa, Vector* posb, float pad)
{
    if (!posa || !posb) return -1;
    if (!ISINRANGE(h, MAX_HUMANS)) return -1;
    return lineIntersectHuman_game(h, posa, posb, pad);
}

int lineintersectvehicle(int v, Vector* posa, Vector* posb, int wheels)
{
    if (!posa || !posb) return -1;
    if (!ISINRANGE(v, MAX_VEHICLES)) return -1;
    return lineIntersectVehicle_game(v, posa, posb, wheels);
}

int lineintersectlevel(Vector* posa, Vector* posb, int cityobjects)
{
    if (!posa || !posb) return -1;
    return lineIntersectLevel_game(posa, posb, cityobjects);
}

void playergivewanted(int p, int victim, int base)
{
    if (!ISINRANGE(p, MAX_PLAYERS) || !ISINRANGE(victim, MAX_PLAYERS)) return;
    playerGiveWantedLevel_game(p, victim, base);
}

int itemgetbillval(int i)
{
    if (!ISINRANGE(i, MAX_ITEMS)) return -1;
    return itemCashGetBillValue_game(i);
}

int itemaddbill(int i, int pos, int amount)
{
    if (!ISINRANGE(i, MAX_ITEMS)) return -1;
    return itemCashAddBill_game(i, pos, amount);
}

void itemremovebill(int i, int amount)
{
    if (!ISINRANGE(i, MAX_ITEMS)) return;
    itemCashRemoveBill_game(i, amount);
}

int itemsetmemotext(int i, char* text)
{
    if (!ISINRANGE(i, MAX_ITEMS)) return -1;
    if (strlen(text) > 1023) return -1;
    return itemSetMemo_game(i, text);
}

int itemnetworkcomputerline(int i, unsigned int line)
{
    if (!ISINRANGE(i, MAX_ITEMS)) return -1;
    return itemComputerTransmitLine_game(i, line);
}