//
// Created by W on 9/20/20.
//
#include "willow.hpp"
#include<iostream>
#include "willow/messaging/Messages.hpp"
#include"willow/root/FileSystem.hpp"
#include "willow/DefaultAssets.hpp"
#include "willow/rendering/Mesh.hpp"
#include"willow/root/Root.hpp"
#include"willow/ecs/EntityComponentSystem.hpp"
#include"willow/window/Window.hpp"
#include"willow/input/InputManager.hpp"
#include"willow/rendering/PerspectiveCamera3D.hpp"
#include"willow/rendering/Renderer.hpp"
#include"willow/ecs/Systems.hpp"
using namespace  wlo;
using namespace  wlo::data;

struct RigidBody{
    wlo::Vec3 velocity;
    wlo::Vec3 acceleration;
};

struct Transform{
    wlo::Vec3 position;
};

struct Gravity{
    wlo::Vec3 vector;
};
namespace wlo::data{
    RegTwoMemberType(RigidBody,"velocity",Vec3,"acceleration",Vec3);
    RegOneMemberType(Transform,"position",Vec3);
    RegOneMemberType(Gravity,"vector",Vec3);
}


System PhysicsIntegrate{
    .settings = Value(Type("settings",{{"dt",typeOf<float>()}}))
};

System Render{
};


class CubeExample:public Messenger{
public:
    UniquePointer<EntityComponentSystem> ecs;
    UniquePointer<Window> window;
    UniquePointer<InputManager> input;
    rendering::Renderer renderer;
    PerspectiveCamera3D camera;
    bool m_shouldStop = false;
    CubeExample() {
        window = CreateUniquePointer<Window>(Window::Info{});
        input = CreateUniquePointer<InputManager>();
        ecs = CreateUniquePointer<EntityComponentSystem>();
        window->permit<WindowClosed,CubeExample,&CubeExample::shutdown>(this);
        input->connect(window.get());
        ecs->registerComponent<RigidBody>();
        ecs->registerComponent<Transform>();
        ecs->registerComponent<Gravity>();
        renderer.connect(window.get());
        renderer.setMainCamera(camera);

        for (size_t i =-100; i < 100; i++){
            auto ent = ecs->spawnEntity<RigidBody,Transform,Gravity>();
            ecs->writeEntity(ent,Transform{.position = {i,i,i}});
            ecs->writeEntity(ent,Gravity{.vector = {0,i,0}});
        }
    }

    void shutdown(const WindowClosed & ){
        m_shouldStop = true;
    }

    void updatePhysics(){
        const float dt = 0.0005;
        auto ents = ecs->getEntitiesOfArchetype<RigidBody,Transform,Gravity>();
        for (auto ent : ents){
            auto rb = ecs->getComponent<RigidBody>(ent);
            auto tform = ecs->getComponent<Transform>(ent);
            auto gravity = ecs->getComponent<Gravity>(ent);
            rb.acceleration +=gravity.vector;
            rb.velocity +=rb.acceleration*dt;
            tform.position +=rb.velocity;
        }
    }

    void draw(){

    }

    void Run( ){
        while(! window->shouldClose()){
            updatePhysics();
            draw();
        }
    }
};


int main(int argc, char ** argv){

    CubeExample example;
    example.Run();

}

