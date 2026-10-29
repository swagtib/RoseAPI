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

#include <math.h>
#include <roseapi.h>

void vectorcopy(Vector* copyto, Vector* copyfrom)
{
    copyto->x = copyfrom->x;
    copyto->y = copyfrom->y;
    copyto->z = copyfrom->z;
}

void vectorzero(Vector* v)
{
    v->x = 0;
    v->y = 0;
    v->z = 0;
}

float vectorlengthsquared(Vector* v)
{
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

void vectorset(Vector* v, float x, float y, float z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

float vectorlength(Vector* v)
{
    return sqrtf(vectorlengthsquared(v));
}

void vectornormalize(Vector* v)
{
    float len = vectorlength(v);
    float inv = 1.0f / len;
    v->x *= inv;
    v->y *= inv;
    v->z *= inv;
}

int vectorincuboid(Vector* v, Vector* min, Vector* max)
{
    return v->x >= min->x && v->x <= max->x &&
    v->y >= min->y && v->y <= max->y &&
    v->z >= min->z && v->z <= max->z;
}

void vectorscale(Vector* v, float scalar)
{
    v->x *= scalar;
    v->y *= scalar;
    v->z *= scalar;
}

void vectorneg(Vector* v)
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

void vectorsub(Vector* v, Vector* sub)
{
    v->x -= sub->x;
    v->y -= sub->y;
    v->z -= sub->z;
}

void vectoradd(Vector* v, Vector* add)
{
    v->x += add->x;
    v->y += add->y;
    v->z += add->z;
}

float vectordot(Vector* a, Vector* b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

void vectorcross(Vector* result, Vector* a, Vector* b)
{
    float x = a->z * b->y - a->y * b->z;
    float y = a->x * b->z - a->z * b->x;
    float z = a->y * b->x - a->x * b->y;
    result->x = x;
    result->y = y;
    result->z = z;
}

float vectordistancesquared(Vector* a, Vector* b)
{
    Vector vec;
    vec.x = a->x - b->x;
    vec.y = a->y - b->y;
    vec.z = a->z - b->z;
    float distsquared = vectorlengthsquared(&vec);
    return distsquared;
}

float vectordistance(Vector* a, Vector* b)
{
    return sqrtf(vectordistancesquared(a, b));
}

int vectorinsphere(Vector* point, Vector* center, float radius)
{
    return vectordistancesquared(point, center) <= radius * radius;
}

void pitchtorotmatrix(RotMatrix *result, float pitch)
{
    float s = sinf(pitch);
    float c = cosf(pitch);
    Vector xaxis = {1, 0, 0};
    Vector zaxis = {0, c, -s};
    Vector yaxis = {0, s, c};
    result->xaxis = xaxis;
    result->yaxis = yaxis;
    result->zaxis = zaxis;
}

void yawtorotmatrix(RotMatrix *result, float yaw)
{
    float s = sinf(yaw);
    float c = cosf(yaw);
    Vector xaxis = {c, 0, s};
    Vector yaxis = {0, 1, 0};
    Vector zaxis = {-s, 0, c};
    result->xaxis = xaxis;
    result->yaxis = yaxis;
    result->zaxis = zaxis;
}

void rolltorotmatrix(RotMatrix *result, float roll)
{
    float s = sinf(roll);
    float c = cosf(roll);
    Vector xaxis = {c, -s, 0};
    Vector yaxis = {s, c, 0};
    Vector zaxis = {0, 0, 1};
    result->xaxis = xaxis;
    result->yaxis = yaxis;
    result->zaxis = zaxis;
}

void vectorrotate(Vector *v, RotMatrix *r)
{
    float x = v->x;
    float y = v->y;
    float z = v->z;
    v->x = r->xaxis.x * x + r->yaxis.x * y + r->zaxis.x * z;
    v->y = r->xaxis.y * x + r->yaxis.y * y + r->zaxis.y * z;
    v->z = r->xaxis.z * x + r->yaxis.z * y + r->zaxis.z * z;
}

void rotmatrixmul(RotMatrix* result, RotMatrix* a, RotMatrix* b)
{
    RotMatrix tmp;
    tmp.xaxis = a->xaxis;
    tmp.yaxis = a->yaxis;
    tmp.zaxis = a->zaxis;
    vectorrotate(&tmp.xaxis, b);
    vectorrotate(&tmp.yaxis, b);
    vectorrotate(&tmp.zaxis, b);
    *result = tmp;
}

void eulertorotmatrix(RotMatrix* result, Vector* euler)
{
    RotMatrix pitch, yaw, roll;
    pitchtorotmatrix(&pitch, euler->x);
    yawtorotmatrix(&yaw, euler->y);
    rolltorotmatrix(&roll, euler->z);
    RotMatrix tmp;
    rotmatrixmul(&tmp, &yaw, &pitch);
    rotmatrixmul(result, &tmp, &roll);
}

void vectorlerp(Vector* result, Vector *a, Vector *b, float t)
{
    result->x = a->x + (b->x - a->x) * t;
    result->y = a->y + (b->y - a->y) * t;
    result->z = a->z + (b->z - a->z) * t;
}

int vectorequals(Vector* a, Vector* b, float epsilon)
{
    return fabsf(a->x - b->x) <= epsilon &&
           fabsf(a->y - b->y) <= epsilon &&
           fabsf(a->z - b->z) <= epsilon;
}

void vectorsetlength(Vector* v, float length)
{
    vectornormalize(v);
    vectorscale(v, length);
}

void rotmatrixtranspose(RotMatrix* result, RotMatrix* m)
{
    RotMatrix t;
    vectorset(&t.xaxis, m->xaxis.x, m->yaxis.x, m->zaxis.x);
    vectorset(&t.yaxis, m->xaxis.y, m->yaxis.y, m->zaxis.y);
    vectorset(&t.zaxis, m->xaxis.z, m->yaxis.z, m->zaxis.z);
    *result = t;
}

void vectorrotateinverse(Vector *vec, RotMatrix *m)
{
    float x = vectordot(vec, &m->xaxis);
    float y = vectordot(vec, &m->yaxis);
    float z = vectordot(vec, &m->zaxis);
    vectorset(vec, x, y, z);
}

void rotmatrixtoeuler(Vector* result, RotMatrix* r)
{
    float pitch = atan2f(-r->yaxis.z, r->zaxis.z);
    float yaw = atan2f(r->xaxis.z, sqrtf(r->yaxis.z * r->yaxis.z + r->zaxis.z * r->zaxis.z));
    float roll = atan2f(-r->yaxis.x, r->xaxis.x);
    if (r->zaxis.z < 0)
    {
        yaw = -yaw - M_PI;
        pitch += M_PI;
    }
    result->x = pitch;
    result->y = yaw;
    result->z = roll;
}