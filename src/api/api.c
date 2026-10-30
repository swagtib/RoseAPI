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

void bonddelete(int id)
{
    if (!ISINRANGE(id, MAX_BONDS)) return;
    deleteBond_game(id);
}

void eventcreatebullet(BulletTypeIndex bt, Vector* pos, Vector* vel, int item)
{
    if (!pos || !vel) return;
    if (!ISINRANGE(bt, BULLETTYPE_COUNT) || !ISINRANGE(item, MAX_ITEMS)) return;
    createEventBullet_game(bt, pos, vel, item);
}

void eventcreatebullethit(BulletHitTypeIndex bht, Vector* pos, Vector* normal)
{
    if (!pos || !normal) return;
    if (!ISINRANGE(bht, BULLETHIT_COUNT)) return;
    createEventBulletHit_game(0, bht, pos, normal);
}

void eventcreatemessage(MessageTypeIndex mt, char *m, int speaker, int dist)
{
    if (!m) return;
    if (!ISINRANGE(mt, MESSAGETYPE_COUNT)) return;
    if (strlen(m) > 63) return;
    createEventMessage_game(mt, m, speaker, dist);
}

void eventcreatevehicletypeupdate(int v)
{
    if (!ISINRANGE(v, MAX_VEHICLES)) return;
    createEventCreateVehicle_game(v);
}

void eventcreatevehicleupdate(int v, VehicleUpdateIndex u, int part, Vector* pos, Vector* hvel)
{
    if (!pos || !hvel) return;
    if (!ISINRANGE(v, MAX_VEHICLES) || !ISINRANGE(u, VEHICLEUPDATE_COUNT)) return;
    createEventUpdateVehicle_game(v, u, part, pos, hvel);
}

void eventcreateupdateitem(int i)
{
    if (!ISINRANGE(i, MAX_ITEMS)) return;
    createEventUpdateItemInfo_game(i);
}

void eventcreateupdateplayer(int i, int finance)
{
    if (!ISINRANGE(i, MAX_PLAYERS)) return;
    if (finance)
    {
        createEventUpdatePlayerFinance_game(i);
    } else createEventUpdatePlayer_game(i);
}

void eventcreatesound(SoundIndex s, Vector* p, float vol, float pitch)
{
    if (!p) return;
    if (!ISINRANGE(s, SOUND_COUNT)) return;
    createEventSound_game(s, p, vol, pitch);
}

void eventcreatesounditem(SoundIndex s, int i, float vol, float pitch)
{
    if (!ISINRANGE(s, SOUND_COUNT) || !ISINRANGE(i, MAX_ITEMS)) return;
    createEventSoundItem_game(s, i, vol, pitch);
}

void eventcreateupdatecorp(int c, int opaque, int dm) // cannot wait to write docs
{
    if (!ISINRANGE(c, MAX_CORPS)) return;
    if (dm)
    {
        createEventUpdateCorpDoorState_game(c, opaque);
    } else createEventUpdateCorpMission_game(c, opaque);
}

void eventcreateupdateelim(int p, int tracker, int team, int savior, Vector* saviorpos)
{
    if (!saviorpos) return;
    if (!ISINRANGE(p, MAX_PLAYERS) || !ISINRANGE(team, MAX_CORPS) || !ISINRANGE(savior, MAX_PLAYERS)) return;
    createEventUpdateElimState_game(p, tracker, team, savior, saviorpos);
}

void eventcreateexplosion(Vector* pos)
{
    if (!pos) return;
    createEventExplosion_game(0, pos); // afaik there's no other explosion types
}

void playergivewanted(int p, int victim, int basepoints)
{
    if (!ISINRANGE(p, MAX_PLAYERS) || !ISINRANGE(victim, MAX_PLAYERS)) return;
    playerGiveWantedLevel_game(p, victim, basepoints);
}

void humandelete(int h)
{
    if (!ISINRANGE(h, MAX_HUMANS)) return;
    deleteHuman_game(h);
}

void vehicledelete(int v)
{
    if (!ISINRANGE(v, MAX_VEHICLES)) return;
    deleteVehicle_game(v);
}

void accountssave(void)
{
    saveAccountsServer_game();
}

int humancreate(Vector* pos, RotMatrix* rot, int p)
{
    if (!pos || !rot) return -1;
    if (!ISINRANGE(p, MAX_PLAYERS)) return -1;
    int idx = createHuman_game(pos, rot, p);
    return idx;
}

