#include "stdafx.h"
#include "BodiesControl.h"
#include "Compound.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"

using namespace std;

const string HELP_FILE_NAME = "help.txt";
const string HELP = "help";
const string ADD = "add";
const string GET_MOST_MASSIVE = "getMostMassive";
const string GET_LIGHTEST_IN_WATER = "getLightestInWater";
const string PRINT_ALL = "printAll";
const string END = "end";

const string SPHERE = "Sphere";
const regex ADD_SPHERE_REGEX("(\\s+)(\\d+)(\\s+)?(\\d+)?");

const string PARALLELEPIPED = "Parallelepiped";
const regex ADD_PARALLELEPIPED_REGEX("(\\s+)(\\d+)(\\s+)(\\d+)(\\s+)(\\d+)(\\s+)?(\\d+)?");

const string CONE = "Cone";
const regex ADD_CONE_REGEX("(\\s+)(\\d+)(\\s+)(\\d+)(\\s+)?(\\d+)?");

const string CYLINDER = "Cylinder";
const regex ADD_CYLINDER_REGEX("(\\s+)(\\d+)(\\s+)(\\d+)(\\s+)?(\\d+)?");

const string COMPOUND = "Compound";
const regex ADD_COMPOUND_REGEX("(\\s+)(\\d+)");

const int EMPTY = -1;
const double GRAVITY = 9.8;
const double WATER_DENSITY = 1000;