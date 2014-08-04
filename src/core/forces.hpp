/*
  Copyright (C) 2010,2012,2013,2014 The ESPResSo project
  Copyright (C) 2002,2003,2004,2005,2006,2007,2008,2009,2010 
    Max-Planck-Institute for Polymer Research, Theory Group
  
  This file is part of ESPResSo.
  
  ESPResSo is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  ESPResSo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/
#ifndef _FORCES_HPP
#define _FORCES_HPP
/** \file forces.hpp Force calculation. 
 *
 *  \todo Preprocessor switches for all forces (Default: everything is turned on).
 *  \todo Implement more flexible thermostat, %e.g. which thermostat to use.
 *
 *  For more information see forces.cpp .
 */
#include "config.hpp"
#include "interaction_data.hpp"
#include "actor/Actor.hpp"
#include "actor/ActorList.hpp"

extern ActorList forceActors;

/** \name Exported Functions */
/************************************************************/
/*@{*/

/** Calculate forces.
 *
 *  A short list, what the function is doing:
 *  <ol>
 *  <li> Initialize forces with: \ref friction_thermo_langevin (ghost forces with zero).
 *  <li> Calculate bonded interaction forces:<br>
 *       Loop all local particles (not the ghosts). 
 *       <ul>
 *       <li> FENE
 *       <li> ANGLE (cos bend potential)
 *       </ul>
 *  <li> Calculate non-bonded short range interaction forces:<br>
 *       Loop all \ref IA_Neighbor::vList "verlet lists" of all \ref #cells.
 *       <ul>
 *       <li> Lennard-Jones.
 *       <li> Buckingham.
 *       <li> Real space part: Coulomb.
 *       <li> Ramp.
 *       </ul>
 *  <li> Calculate long range interaction forces:<br>
         Uses <a href=P3M_calc_kspace_forces> P3M_calc_kspace_forces </a>
 *  </ol>
 */
void force_calc();

/** Set forces of all ghosts to zero
*/
void init_forces_ghosts();

/** Check if forces are NAN 
*/
void check_forces();

void 
calc_non_bonded_pair_force_parts(Particle *p1, Particle *p2, IA_parameters *ia_params,
                                 double d[3], double dist, double dist2, 
                                 double force[3], 
                                 double torque1[3] = NULL, double torque2[3] = NULL);

void 
calc_non_bonded_pair_force(Particle *p1, Particle *p2, IA_parameters *ia_params, 
                           double d[3], double dist, double dist2, 
                           double force[3], 
                           double torque1[3] = NULL, double torque2[3] = NULL);

void 
calc_non_bonded_pair_force(Particle *p1, Particle *p2, 
                           double d[3], double dist, double dist2, 
                           double force[3]);

void 
calc_non_bonded_pair_force_from_partcfg(Particle *p1, Particle *p2, 
                                        IA_parameters *ia_params,
                                        double d[3], double dist, double dist2,
                                        double force[3],
                                        double torque1[3] = NULL, 
                                        double torque2[3] = NULL);

void calc_non_bonded_pair_force_from_partcfg_simple(Particle *p1,Particle *p2,double d[3],double dist,double dist2,double force[3]);

/** Calculate non bonded forces between a pair of particles.
    @param p1        pointer to particle 1.
    @param p2        pointer to particle 2.
    @param d         vector between p1 and p2. 
    @param dist      distance between p1 and p2.
    @param dist2     distance squared between p1 and p2. */
void add_non_bonded_pair_force(Particle *p1, Particle *p2, 
                               double d[3], double dist, double dist2);

/** Calculate bonded forces for one particle.
    @param p1 particle for which to calculate forces
*/
void add_bonded_force(Particle *p1);

/** add force to another. This is used when collecting ghost forces. */
void add_force(ParticleForce *F_to, ParticleForce *F_add);

/** add force to another. This is used when collecting ghost forces. */
//void add_force(ParticleForce *F_to, ParticleForce *F_add);

void check_particle_force(Particle *part);

/*@}*/

#endif