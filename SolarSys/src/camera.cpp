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

Camera::Camera()
    : m_fDistance{5}, m_fAngleX{0}, m_fAngleY{0}
{
}

void Camera::moveFront(float delta)
{
    m_fDistance =  (m_fDistance + delta >= 0 ? m_fDistance + delta : m_fDistance);
}

void Camera::rotateLeft(float degrees)
{
    m_fAngleY += degrees;
}

void Camera::rotateUp(float degrees)
{
    m_fAngleX += degrees;
}

glm::mat4 Camera::getViewMatrix() const
{
    glm::mat4 view_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -m_fDistance));
    view_matrix = glm::rotate(view_matrix, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
    view_matrix = glm::rotate(view_matrix, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));
    return view_matrix;
}