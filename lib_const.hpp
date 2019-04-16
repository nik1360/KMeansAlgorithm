#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <omp.h>

#include "csv_reader.hpp"
#include "data_item.hpp"
#include "centroid.hpp"

#define NUM_VARIABLES 3
#define NUM_CENTROIDS 3
#define MAX_ITERATIONS 1000