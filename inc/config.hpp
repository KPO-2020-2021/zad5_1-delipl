/*
 * This file contains definitions made in CMakeLists.txt
 * that we want available in the source code.
 * In the source code, include "exampleConfig.h" (no .in suffix).
 * This header file will be generated, and filled with the
 * right definition values. Change the namings as you wish,
 * but make sure they match up with whats in CMakeLists.txt.
 */
#define PROJECT_VERSION_MAJOR 2
#define PROJECT_VERSION_MINOR 0
#define PROJECT_VERSION_PATCH 0
#define PROJECT_VERSION_TWEAK 0

/**
 * @brief Path to data forlder from root of project where *.dat files are placed
 */
#define DATA_FOLDER "./dat/"

/**
 * @brief Path to temporary forlder from root of project where *.dat files are placed during running program.
 */
#define TMP_FOLDER "./tmp/"

/**
 * @brief Minimal difference between two double numbers. It might be included.
 */
#define MIN_DIFF 0.0000001
