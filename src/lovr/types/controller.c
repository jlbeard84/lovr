#include "lovr/types/controller.h"
#include "lovr/headset.h"
#include "util.h"

void luax_pushcontroller(lua_State* L, Controller* controller) {
  if (controller == NULL) {
    lua_pushnil(L);
    return;
  }

  Controller** userdata = (Controller**) lua_newuserdata(L, sizeof(Controller*));
  luaL_getmetatable(L, "Controller");
  lua_setmetatable(L, -2);
  *userdata = controller;
}

Controller* luax_checkcontroller(lua_State* L, int index) {
  return *(Controller**) luaL_checkudata(L, index, "Controller");
}

const luaL_Reg lovrController[] = {
  { "isPresent", l_lovrControllerIsPresent },
  { "getPosition", l_lovrControllerGetPosition },
  { "getOrientation", l_lovrControllerGetOrientation },
  { "getAxis", l_lovrControllerGetAxis },
  { "isDown", l_lovrControllerIsDown },
  { "getHand", l_lovrControllerGetHand },
  { "vibrate", l_lovrControllerVibrate },
  { NULL, NULL }
};

int l_lovrControllerIsPresent(lua_State* L) {
  Controller* controller = luax_checkcontroller(L, 1);
  lua_pushboolean(L, lovrHeadsetControllerIsPresent(controller));
  return 1;
}

int l_lovrControllerGetPosition(lua_State* L) {
  Controller* controller = luax_checkcontroller(L, 1);
  float x, y, z;
  lovrHeadsetControllerGetPosition(controller, &x, &y, &z);
  lua_pushnumber(L, x);
  lua_pushnumber(L, y);
  lua_pushnumber(L, z);
  return 3;
}

int l_lovrControllerGetOrientation(lua_State* L) {
  Controller* controller = luax_checkcontroller(L, 1);
  float w, x, y, z;
  lovrHeadsetControllerGetOrientation(controller, &w, &x, &y, &z);
  lua_pushnumber(L, w);
  lua_pushnumber(L, x);
  lua_pushnumber(L, y);
  lua_pushnumber(L, z);
  return 4;
}

int l_lovrControllerGetAxis(lua_State* L) {
  Controller* controller = luax_checkcontroller(L, 1);
  ControllerAxis* axis = (ControllerAxis*) luax_checkenum(L, 2, &ControllerAxes, "controller axis");
  lua_pushnumber(L, lovrHeadsetControllerGetAxis(controller, *axis));
  return 1;
}

int l_lovrControllerIsDown(lua_State* L) {
  Controller* controller = luax_checkcontroller(L, 1);
  ControllerButton* button = (ControllerButton*) luax_checkenum(L, 2, &ControllerButtons, "controller button");
  lua_pushboolean(L, lovrHeadsetControllerIsDown(controller, *button));
  return 1;
}

int l_lovrControllerGetHand(lua_State* L) {
  Controller* controller = luax_checkcontroller(L, 1);
  lua_pushstring(L, map_int_find(&ControllerHands, lovrHeadsetControllerGetHand(controller)));
  return 1;
}

int l_lovrControllerVibrate(lua_State* L) {
  Controller* controller = luax_checkcontroller(L, 1);
  float duration = luaL_optnumber(L, 2, .5);
  lovrHeadsetControllerVibrate(controller, duration);
  return 0;
}
