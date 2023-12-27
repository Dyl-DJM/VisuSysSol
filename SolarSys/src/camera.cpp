/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  Module defining the Camera class and it's methods =
=													 =
======================================================
*/

#include "../include/camera.hpp"


/**
 * @brief Constructor
*/
Camera::Camera()
    : m_fDistance{5}
    , m_fAngleX{0}
    , m_fAngleY{0}
    , position {glm::vec3(0, 0, 0)}
    , view_matrix { glm::mat4(0)}
{}

/**
 * @brief Move the camera forward.
 * 
 * @param delta Number of unit to move forward (or backward if negative) from.
*/
void Camera::moveFront(float delta)
{
    m_fDistance =  (m_fDistance + delta > 0 ? m_fDistance + delta : m_fDistance);
}

/**
 * @brief Rotate the camera horizontally.
 * 
 * @param degrees Angle in degree to rotate horizontally for. Positive degree will rotate left, negate will rotate right.
*/
void Camera::rotateLeft(float degrees)
{
    m_fAngleY += degrees;
}

/**
 * @brief Rotate the camera vertically.
 * 
 * @param degree Angle in degree to rotate vertically for. Positive degree will rotate up, negate will rotate down.
*/
void Camera::rotateUp(float degrees)
{
    m_fAngleX += degrees;
}

glm::mat4 Camera::getViewMatrix() const
{
    // glm::mat4 view_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, - m_fDistance));
    // view_matrix = glm::rotate(view_matrix, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
    // view_matrix = glm::rotate(view_matrix, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));
    // return view_matrix;
    return view_matrix;
}

/**
 * @brief Update the camera's position depending on the target planet's position
 * 
 * @param targetPosition the position of the targeted planet
*/
void Camera::update_position(glm::vec4 targetPosition){

    // The position of the camera before transformation
    glm::vec3 cameraPosition = glm::vec3(0.f, 0.f, -m_fDistance);

    // rotation matrix
    glm::mat4 rotation = glm::rotate(glm::mat4(1.f), glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
    rotation = glm::rotate(rotation, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));

    // Update the position after rotation transformation
    cameraPosition = glm::vec3(rotation * glm::vec4(cameraPosition, 1.f)); // Add 1.f because it's a position

    glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

    // Set the camera's position and look-at target
    position.x = targetPosition.x + cameraPosition.x;
    position.y = targetPosition.y + cameraPosition.y;
    position.z = targetPosition.z + cameraPosition.z;
    view_matrix = glm::lookAt(position, glm::vec3(targetPosition), upVector);
}

/**
 * @brief Set a distance for the camera
 * 
 * @param distance The distance to set
*/
void Camera::set_distance(float distance){
    if (distance < 1.){
        m_fDistance = 1.;
    }
    else {
        m_fDistance = distance;
    }
}