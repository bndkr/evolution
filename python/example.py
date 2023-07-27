import pyEvolution as evolution

width = 760
height = 512

window = evolution.setup(True, width, height)

evolution.add_textures_from_dir("C:/dev/evolution/example/assets/example/textures")

quad = evolution.create_texture_quad()

# todo: make this a default constructor
camera = evolution.Camera(evolution.Float3(), evolution.Float3(), width, height)

while True:
    pass
