#pragma once

enum class menu_event
{
    PlayerLeave,
    PlayerJoin,
    PlayerMgrInit,
    PlayerMgrShutdown,
    MenuUnloaded,
    Wndproc,
    Draw,

    // Gameplay functions
    AddPlaneLift,
    ApplyPlaneThrust,
};