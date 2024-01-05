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
 * @brief Constructor.
 *
 * @param distToCenter A distance on z axis from the center of the scene.
 * @param angle A degree value representing the camera rotation around the x-axis.
 */
Camera::Camera()
    : m_fDistance{initialDistance}, m_fAngleX{initialAngleX}, m_fAngleY{initialAngleY}, position{glm::vec3(0, 0, 0)}
{
    initialConfig();
}

/**
 * @brief Makes a basic view Matrix computation.
 *
 * Computes the camera view matrix thanks to distance and angles information.
 */
void Camera::initialConfig()
{
    view_matrix = glm::translate(glm::mat4(1), glm::vec3(0.f, 0.f, -m_fDistance));
    view_matrix = glm::rotate(view_matrix, glm::radians(m_fAngleX), glm::vec3(1, 0, 0));
    view_matrix = glm::rotate(view_matrix, glm::radians(m_fAngleY), glm::vec3(0, 1, 0));
}

/**
 * @brief Move the camera forward.
 *
 * @param delta Number of unit to move forward (or backward if negative) from.
 */
void Camera::moveFront(float delta)
{
    m_fDistance = (m_fDistance + delta > 0.1 ? m_fDistance + delta : m_fDistance);
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
    if (_pov != PROFILE) // We want to rotate up only if we are in the default/initial mode where we are allowed to rotate arround this axis too
    {
        m_fAngleX += degrees;
    }
}

/**
 * @brief Returns the camera view matrix.
 */
glm::mat4 Camera::getViewMatrix() const
{
    return view_matrix;
}

/**
 * @brief Update the camera's position depending on the target planet's position
 *
 * @param targetPosition the position of the targeted planet
 */
void Camera::update_position(glm::vec4 targetPosition)
{
    // The position of the camera before transformation
    glm::vec3 cameraPosition = glm::vec3(0.f, 0.f, m_fDistance);

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
void Camera::set_distance(float distance)
{
    if (distance < 0.25)
    {
        m_fDistance = 0.25;
    }
    else
    {
        m_fDistance = distance;
    }
}

/**
 * @brief Checks if the camera is currently in the focused mode.
 *
 * @return True if the camera is currently in the focused mode and false otherwise.
 */
bool Camera::isFocusedPov()
{
    return _pov == FOCUSED;
}

/**
 * @brief Sets the camera in the focused mode.
 */
void Camera::setFocusedPov()
{
    _pov = FOCUSED;
    m_fAngleX = 15; // When returning to focus mode from initial POV, set the angle X to 15.
    m_fAngleY = 0;  // When returning to focus mode from initial POV, set the angle Y to 0.
}

/**
 * @brief Checks if the camera is currently in the default mode.
 *
 * @return True if the camera is currently in the default mode and false otherwise.
 */
bool Camera::isInitialPov()
{
    return _pov == GENERAL;
}

/**
 * @brief Sets the camera in the default mode.
 */
void Camera::setInitialPov()
{
    // Resetting the camera position
    m_fDistance = initialDistance;
    m_fAngleX = initialAngleX;
    m_fAngleY = initialAngleY;
    _pov = GENERAL;
}

/**
 * @brief Checks if the camera is currently in the profile mode.
 *
 * @return True if the camera is currently in the profile mode and false otherwise.
 */
bool Camera::isProfilePov()
{
    return _pov == PROFILE;
}

/**
 * @brief Sets the camera in the profile mode.
 */
void Camera::setProfilePov()
{
    if (_pov != PROFILE) // Without the condition
    {
        m_fDistance = initialDistance;
        m_fAngleX = 0;  // The profile view is the same as the default/initial but with a a 0 value on X angle
        m_fAngleY = 90; // The initial state of the profil view, must
        _pov = PROFILE;
    }
}