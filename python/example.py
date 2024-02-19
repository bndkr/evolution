import pyEvolution as ev

width = 760
height = 512

window = ev.setup(True, width, height)

ev.add_textures_from_dir("C:/dev/evolution/example/assets/example/textures")
ev.add_programs_from_dir("C:/dev/evolution/example/shaders")

# quad = ev.create_texture_quad()
f = ev.Float3(0, 0, -5)
# quad.set_position(f)

# todo: make this a default constructor
camera = ev.Camera(ev.Float3(), ev.Float3(), width, height)

while not ev.window_should_close(window):
    ev.poll_events()
    windowSize = ev.get_window_size(window)
    ev.update_viewport(0, 0, windowSize.width, windowSize.height)
    camera.update_aspect(windowSize.width, windowSize.height)
    ev.clear_buffer()

    ev.swap_buffers(window)
