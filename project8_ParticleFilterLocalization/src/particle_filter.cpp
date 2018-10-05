/*
 * particle_filter.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: Tiffany Huang
 */

#include <random>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <math.h> 
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>

#include "particle_filter.h"

using namespace std;

void ParticleFilter::init(double x, double y, double theta, double std[]) {
	// TODO: Set the number of particles. Initialize all particles to first position (based on estimates of 
	//   x, y, theta and their uncertainties from GPS) and all weights to 1. 
	// Add random Gaussian noise to each particle.
	// NOTE: Consult particle_filter.h for more information about this method (and others in this file).
	std::default_random_engine gen;
	num_particles=100;
	weights.resize(num_particles);
	particles.resize(num_particles);
	normal_distribution<double> dist_x(x, std[0]);
	normal_distribution<double> dist_y(y, std[1]);
	normal_distribution<double> dist_theta(theta, std[2]);

	for (int i = 0; i < num_particles; i++){
		particles[i].id = i;
		particles[i].x = dist_x(gen);
		particles[i].y = dist_y(gen);
		particles[i].theta = dist_theta(gen);
		particles[i].weight = 1;
		weights[i]=1;
	}	
	is_initialized = true;


}

void ParticleFilter::prediction(double delta_t, double std_pos[], double velocity, double yaw_rate) {
	// TODO: Add measurements to each particle and add random Gaussian noise.
	// NOTE: When adding noise you may find std::normal_distribution and std::default_random_engine useful.
	//  http://en.cppreference.com/w/cpp/numeric/random/normal_distribution
	//  http://www.cplusplus.com/reference/random/default_random_engine/

    std::default_random_engine gen;
   normal_distribution<double> dist_x(0, std_pos[0]);
   normal_distribution<double> dist_y(0, std_pos[1]);
   normal_distribution<double> dist_theta(0, std_pos[2]);


    for (int i = 0; i < num_particles; ++i) {
    
    if (abs(yaw_rate) >0.0001) {
      // Add measurements to particles
      particles[i].x += (velocity/yaw_rate) * (sin(particles[i].theta + (yaw_rate * delta_t)) - sin(particles[i].theta));
      particles[i].y += (velocity/yaw_rate) * (cos(particles[i].theta) - cos(particles[i].theta + (yaw_rate * delta_t)));
      particles[i].theta += yaw_rate * delta_t;
      if (particles[i].theta< 0) particles[i].theta=particles[i].theta+2*M_PI;
      if (particles[i].theta> 2*M_PI) particles[i].theta=particles[i].theta-2*M_PI;
      
    } else {
      // Add measurements to particles
      particles[i].x += velocity * delta_t * cos(particles[i].theta);
      particles[i].y += velocity * delta_t * sin(particles[i].theta);
      // Theta will stay the same due to no yaw_rate
      
    }

    // Add noise to the particles
    particles[i].x += dist_x(gen);
    particles[i].y += dist_y(gen);
    particles[i].theta += dist_theta(gen);

    
  }



}

void ParticleFilter::dataAssociation(std::vector<LandmarkObs> predicted, std::vector<LandmarkObs>& observations) {
	// TODO: Find the predicted measurement that is closest to each observed measurement and assign the 
	//   observed measurement to this particular landmark.
	// NOTE: this method will NOT be called by the grading code. But you will probably find it useful to 
	//   implement this method and use it as a helper during the updateWeights phase.


}

void ParticleFilter::updateWeights(double sensor_range, double std_landmark[], 
		const std::vector<LandmarkObs> &observations, const Map &map_landmarks) {
	// TODO: Update the weights of each particle using a mult-variate Gaussian distribution. You can read
	//   more about this distribution here: https://en.wikipedia.org/wiki/Multivariate_normal_distribution
	// NOTE: The observations are given in the VEHICLE'S coordinate system. Your particles are located
	//   according to the MAP'S coordinate system. You will need to transform between the two systems.
	//   Keep in mind that this transformation requires both rotation AND translation (but no scaling).
	//   The following is a good resource for the theory:
	//   https://www.willamette.edu/~gorr/classes/GeneralGraphics/Transforms/transforms2d.htm
	//   and the following is a good resource for the actual equation to implement (look at equation 
	//   3.33
	//   http://planning.cs.uiuc.edu/node99.html
	// Step 1: For each particle , transfer the observation to world corrdinate
	// Step 2: Use sensor_range to filt the landmarks in map_landmarks as predicted landmark
	// Step 3: Associate observed landmarks with predicted landmarks
	// Step 4: Calculate multi-gaussian and update weight

	
	const double gaussian_norm = 1 / (2 * M_PI * std_landmark[0] * std_landmark[1]);
  	const double sig_x = 2 * std_landmark[0] * std_landmark[0];
  	const double sig_y = 2 * std_landmark[1] * std_landmark[1];

  	for (int i = 0; i < num_particles; i++) {
  		double posterior_probability=1.0;

  		
  		for (int j = 0; j < observations.size(); j++) {
  			double map_obs_x, map_obs_y;
      		map_obs_x = observations[j].x * cos(particles[i].theta) - observations[j].y * sin(particles[i].theta) + particles[i].x;
      		map_obs_y = observations[j].x * sin(particles[i].theta) + observations[j].y * cos(particles[i].theta) + particles[i].y;
      		double nearest_dist=1000000.0;
      		double exponent=0.0;
      		vector<Map::single_landmark_s> landmarks = map_landmarks.landmark_list;
      		int chose=0;
      		for (int k = 0; k < landmarks.size(); k++) {

      			double landmark_part_dist = sqrt(pow(particles[i].x - landmarks[k].x_f, 2) + pow(particles[i].y - landmarks[k].y_f, 2));
      			if (landmark_part_dist<2*sensor_range){
      				double landmark_obs_dist= sqrt(pow(map_obs_x - landmarks[k].x_f, 2) + pow(map_obs_y - landmarks[k].y_f, 2));
      				if (landmark_obs_dist<nearest_dist){
      					nearest_dist=landmark_obs_dist;
      					exponent=pow(map_obs_x - landmarks[k].x_f, 2)/ sig_x + pow(map_obs_y - landmarks[k].y_f, 2)/sig_y;
      					chose=k;
      				}

      			}
      		}
      		landmarks.erase(landmarks.begin() + chose);
      		posterior_probability=posterior_probability*gaussian_norm * exp(-exponent);

  		}
  		particles[i].weight = posterior_probability;
    	ParticleFilter::weights[i] = particles[i].weight;
  	}

  	double sum_weight=0.0;
  	for (int i = 0; i < ParticleFilter::weights.size(); i++) {
  		sum_weight=sum_weight+ParticleFilter::weights[i];
  	}
  	 for (int i = 0; i < ParticleFilter::weights.size(); i++) {
  		ParticleFilter::weights[i] =ParticleFilter::weights[i] /sum_weight;
      particles[i].weight=ParticleFilter::weights[i] /sum_weight;
  	}
}

void ParticleFilter::resample() {
	// TODO: Resample particles with replacement with probability proportional to their weight. 
	// NOTE: You may find std::discrete_distribution helpful here.
	//   http://en.cppreference.com/w/cpp/numeric/random/discrete_distribution
	std::random_device rd;
	std::mt19937 generator(rd());

	std::vector<Particle> particles_temp = particles;
  std::discrete_distribution <int> distribution(weights.begin(),weights.end());

	for(int i=0; i<num_particles; i++)	{
			int number = distribution(generator);
      		particles_temp[i].id = number;
			particles_temp[i].x  = particles[number].x;
			particles_temp[i].y  = particles[number].y;
      particles_temp[i].theta  = particles[number].theta;
		}
	particles = particles_temp; // new particles after resmaple


}

Particle ParticleFilter::SetAssociations(Particle& particle, const std::vector<int>& associations, 
                                     const std::vector<double>& sense_x, const std::vector<double>& sense_y)
{
    //particle: the particle to assign each listed association, and association's (x,y) world coordinates mapping to
    // associations: The landmark id that goes along with each listed association
    // sense_x: the associations x mapping already converted to world coordinates
    // sense_y: the associations y mapping already converted to world coordinates

    particle.associations= associations;
    particle.sense_x = sense_x;
    particle.sense_y = sense_y;
}

string ParticleFilter::getAssociations(Particle best)
{
	vector<int> v = best.associations;
	stringstream ss;
    copy( v.begin(), v.end(), ostream_iterator<int>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length()-1);  // get rid of the trailing space
    return s;
}
string ParticleFilter::getSenseX(Particle best)
{
	vector<double> v = best.sense_x;
	stringstream ss;
    copy( v.begin(), v.end(), ostream_iterator<float>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length()-1);  // get rid of the trailing space
    return s;
}
string ParticleFilter::getSenseY(Particle best)
{
	vector<double> v = best.sense_y;
	stringstream ss;
    copy( v.begin(), v.end(), ostream_iterator<float>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length()-1);  // get rid of the trailing space
    return s;
}
