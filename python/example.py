import pyEvolution as evolution

width = 760
height = 512

window = evolution.setup(True, width, height)

evolution.add_textures_from_dir("C:/dev/evolution/example/assets/example/textures")
evolution.add_programs_from_dir("C:/dev/evolution/example/shaders")

quad = evolution.create_texture_quad()
# quad.move(evolution.Float3(0, 0, -5))

vec = evolution.Float3(0, 0, 0)
evolution.move_vector(vec)

# todo: make this a default constructor
camera = evolution.Camera(evolution.Float3(), evolution.Float3(), width, height)

while not evolution.window_should_close(window):
    evolution.poll_events()
    curr_width, curr_height = evolution.get_window_size(window)
    evolution.update_viewport(curr_width, curr_height)
    camera.update_aspect(curr_width, curr_height)
    evolution.clear_buffer()

    evolution.swap_buffers(window)
