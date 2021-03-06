/***************************************************************************

 Copyright (c) 2014 The Board of Trustees of the Leland Stanford Junior University.
 All rights reserved.
 Contact: Okai Addy <noaddy@alumni.stanford.edu>

 This source code is under a BSD 3-Clause License.
 See LICENSE for more information.

To distribute this file, substitute the full license for the above reference.

**************************************************************************/
#ifndef SPIRAL_H
#define SPIRAL_H

#include "trajectory.h"
#include "variabledensity.h"

/**
 \ingroup	trajectory
 \defgroup	spiral	Spiral
 @{ 
*/

/**
 \defgroup	spiral	Spirals
 @{
*/

enum SpiralDirection{spOUT, spINOUT};
enum spMETHOD{spmVDS, spmMINTIME};
enum SpiralType{ARCHIMEDEAN, spFERMAT};

struct StackOfSpirals
{
  struct Trajectory* spirals;
  struct PhaseEncoder* phaseEncoder;
};
/**
 \brief	Calculate the sampling density compensation weights based on curvature and spacing of samples
 \param[in]	gx	x gradient values (G/cm)
 \param[in]	gy	y gradient values (G/cm)
*/
void calcSpiralDcf(float *gx, float *gy, float *kx, float *ky, int rolen, float *denscomp);


/**
 \param[in]	spatialResolution	Resolution (mm)
 \param[in]	readoutDuration	Waveform duration (sec)
 \param[in]	samplingInterval	Sampling period (sec)
 \param[in]	gmax	Gradient amplitude limit (G/cm)
 \param[in]	smax	Slew rate limit (G/cm/s)
*/
struct Trajectory* generateSpirals(struct VariableDensity *vd, float fieldOfView, float spatialResolution, float readoutDuration, int rewindTrajectory, float samplingInterval, int interleaves, enum SpiralType sptype, float floretAngle, float readoutFieldOfView, float gmax, float smax);

struct StackOfSpirals* newStackOfSpirals(struct Trajectory *spirals, struct PhaseEncoder* phaseEncoder);

/*!
 * \brief Free the memory of a stack of spirals trajectory.
 * \param spirals Stack of spirals trajectory.
 */
void deleteStackOfSpirals(struct StackOfSpirals** spirals);

struct StackOfSpirals* generateStackOfSpirals(struct VariableDensity *variableDensity, float fieldOfViewXY, float fieldOfViewZ, float spatialResolutionXY, float spatialResolutionZ, float readoutDuration, int balance, float samplingInterval, int numInterleaves, float readoutFieldOfView, float maxGradientAmplitude, float maxSlewRate);
struct Trajectory* stackOfSpiralsToTrajectory(struct StackOfSpirals* stackOfSpirals, enum WaveformStorageType storageType);
/** @} */

#endif

