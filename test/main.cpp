#include <dokun_ui.hpp>
//using namespace dokun;

#include <memory> // std::unique_ptr

// GL error checking
void check_error(){
    switch (glGetError()){
    case 0: return;
    case GL_INVALID_ENUM: fprintf(stderr, "GL error: Invalid enum\n"); break;
    case GL_INVALID_VALUE: fprintf(stderr, "GL error: Invalid value\n"); break;
    case GL_INVALID_OPERATION: fprintf(stderr, "GL error: Invalid operation\n"); break;
    case GL_STACK_OVERFLOW: fprintf(stderr, "GL error: Stack overflow\n"); break;
    case GL_STACK_UNDERFLOW: fprintf(stderr, "GL error: Stack underflow\n"); break;
    case GL_OUT_OF_MEMORY: fprintf(stderr, "GL error: Out of memory\n"); break;
    case GL_TABLE_TOO_LARGE: fprintf(stderr, "GL error: Table too large\n"); break;
    default: fprintf(stderr, "GL error: Unknown\n");
    }
}

int main() {
    #ifdef DOKUN_USE_GLFW
    std::cout << "DOKUN_USE_GLFW - ON\n";
    #else
    std::cout << "DOKUN_USE_GLFW - OFF\n";
    #endif 
    #ifdef DOKUN_USE_OPENGL
    std::cout << "DOKUN_USE_OPENGL - ON\n";
    #else
    std::cout << "DOKUN_USE_OPENGL - OFF\n";
    #endif 
    #ifdef DOKUN_USE_VULKAN
    std::cout << "DOKUN_USE_VULKAN - ON\n";
    #else
    std::cout << "DOKUN_USE_VULKAN - OFF\n\n";
    #endif         
    // Initialize engine
    if(!dokun::Engine::open()) {
        std::cout << DOKUN_UI_TAG "engine failed to initialize" << std::endl;
        return 1;
    }
    // Create a window context     // causes Segfault when allocating via heap
    // todo: creating a Window unique_ptr or an object on the heap causes a malloc error (when not using GLFW). Fix this soon
    dokun::Window window;
    //dokun::Window * window = new dokun::Window();
    //std::unique_ptr<dokun::Window> window = std::unique_ptr<dokun::Window>(new dokun::Window());//std::make_unique<dokun::Window>(); // C++14 :/
    window.create("Test", 1280, 720, 0);
    window.show();
    
    dokun::Label * label = new dokun::Label();//("Hello World"); // causes Segfault when allocating via stack
    label->set_position(10, 10);
    
	while(window.is_open())
	{
        window.set_viewport(window.get_client_width(), window.get_client_height()); // causes "X connection to ? broken (explicit kill or server shutdown)." error
        window.clear(32, 32, 32);	    
	
	    // Draw here ...
	    label->draw(); // Not showing for some reason
	
		window.update();      
		window.poll_events();
		check_error();
	}
	
	window.destroy();
	
	glfwTerminate();//dokun::Engine::close();
	
    return 0;
}
