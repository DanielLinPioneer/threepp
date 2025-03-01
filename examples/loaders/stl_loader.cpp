
#include <threepp/threepp.hpp>

using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 100);
    camera->position.z = 1;

    OrbitControls controls{camera, canvas};

    STLLoader loader;
    auto geometry = loader.load("data/models/stl/pr2_head_pan.stl");
    auto material = MeshPhongMaterial::create({{"flatShading", true}, {"color", Color::brown}});
    auto mesh = Mesh::create(geometry, material);
    mesh->scale *= 2;
    mesh->rotateX(-math::PI / 2).rotateZ(math::PI / 2);
    scene->add(mesh);

    auto wireframeMaterial = LineBasicMaterial::create();
    wireframeMaterial->color *= 0.1f;
    wireframeMaterial->opacity = 0.25f;
    wireframeMaterial->transparent = true;
    auto wireframe = LineSegments::create(WireframeGeometry::create(*geometry), wireframeMaterial);
    mesh->add(wireframe);

    auto light = HemisphereLight::create(Color::aliceblue, Color::grey);
    scene->add(light);

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {
        mesh->rotation.z += 1 * dt;

        renderer.render(scene, camera);
    });
}
