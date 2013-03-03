######################################################################
# Created by Stephen Aldriedge on 1/29/13
######################################################################

CONFIG(debug, debug|release) {
    DESTDIR = bin/debug
	LIBS += -LSFML-2.0_1-17-13/lib/windows -lopengl32 -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
} else {
    DESTDIR = bin/release
	LIBS += -LSFML-2.0_1-17-13/lib/windows -lopengl32 -lsfml-graphics -lsfml-window -lsfml-system
}

CONFIG += qt warn_on uitools console
TEMPLATE = app
TARGET = $${PROJECT}
OBJECTS_DIR = $${DESTDIR}/.o
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR = $${DESTDIR}/.rcc
UI_DIR = $${DESTDIR}/.ui

DEPENDPATH += include \
              src \


INCLUDEPATH += . \
               include \
			   SFML-2.0_1-17-13/include

# Input
HEADERS += include/Application.h \
           include/Color.h \
		   include/libtarga.h \
		   include/Camera.h \
		   include/Events.h \
		   include/Light.h \
		   include/RayTracer.h \
		   include/RenderParams.h \
		   include/Scene.h \
		   include/Shader.h \
		   include/Shapes.h \
		   include/stdafx.h \
		   include/targetver.h \
		   include/Utility.h \
           include/GUI/QSFMLCanvas.hpp \
           include/GUI/renderWindowWrapper.hpp \
           SFML-2.0_1-17-13/include/SFML/Audio.hpp \
           SFML-2.0_1-17-13/include/SFML/Config.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics.hpp \
           SFML-2.0_1-17-13/include/SFML/Network.hpp \
           SFML-2.0_1-17-13/include/SFML/OpenGL.hpp \
           SFML-2.0_1-17-13/include/SFML/System.hpp \
           SFML-2.0_1-17-13/include/SFML/Window.hpp \
           SFML-2.0_1-17-13/include/SFML/Audio/Export.hpp \
           SFML-2.0_1-17-13/include/SFML/Audio/Listener.hpp \
           SFML-2.0_1-17-13/include/SFML/Audio/Music.hpp \
           SFML-2.0_1-17-13/include/SFML/Audio/Sound.hpp \
           SFML-2.0_1-17-13/include/SFML/Audio/SoundBuffer.hpp \
           SFML-2.0_1-17-13/include/SFML/Audio/SoundBufferRecorder.hpp \
           SFML-2.0_1-17-13/include/SFML/Audio/SoundRecorder.hpp \
           SFML-2.0_1-17-13/include/SFML/Audio/SoundSource.hpp \
           SFML-2.0_1-17-13/include/SFML/Audio/SoundStream.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/BlendMode.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/CircleShape.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Color.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/ConvexShape.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Drawable.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Export.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Font.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Glyph.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Image.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/PrimitiveType.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Rect.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/RectangleShape.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/RenderStates.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/RenderTarget.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/RenderTexture.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/RenderWindow.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Shader.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Shape.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Sprite.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Text.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Texture.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Transform.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Transformable.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/Vertex.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/VertexArray.hpp \
           SFML-2.0_1-17-13/include/SFML/Graphics/View.hpp \
           SFML-2.0_1-17-13/include/SFML/Network/Export.hpp \
           SFML-2.0_1-17-13/include/SFML/Network/Ftp.hpp \
           SFML-2.0_1-17-13/include/SFML/Network/Http.hpp \
           SFML-2.0_1-17-13/include/SFML/Network/IpAddress.hpp \
           SFML-2.0_1-17-13/include/SFML/Network/Packet.hpp \
           SFML-2.0_1-17-13/include/SFML/Network/Socket.hpp \
           SFML-2.0_1-17-13/include/SFML/Network/SocketHandle.hpp \
           SFML-2.0_1-17-13/include/SFML/Network/SocketSelector.hpp \
           SFML-2.0_1-17-13/include/SFML/Network/TcpListener.hpp \
           SFML-2.0_1-17-13/include/SFML/Network/TcpSocket.hpp \
           SFML-2.0_1-17-13/include/SFML/Network/UdpSocket.hpp \
           SFML-2.0_1-17-13/include/SFML/System/Clock.hpp \
           SFML-2.0_1-17-13/include/SFML/System/Err.hpp \
           SFML-2.0_1-17-13/include/SFML/System/Export.hpp \
           SFML-2.0_1-17-13/include/SFML/System/InputStream.hpp \
           SFML-2.0_1-17-13/include/SFML/System/Lock.hpp \
           SFML-2.0_1-17-13/include/SFML/System/Mutex.hpp \
           SFML-2.0_1-17-13/include/SFML/System/NonCopyable.hpp \
           SFML-2.0_1-17-13/include/SFML/System/Sleep.hpp \
           SFML-2.0_1-17-13/include/SFML/System/String.hpp \
           SFML-2.0_1-17-13/include/SFML/System/Thread.hpp \
           SFML-2.0_1-17-13/include/SFML/System/ThreadLocal.hpp \
           SFML-2.0_1-17-13/include/SFML/System/ThreadLocalPtr.hpp \
           SFML-2.0_1-17-13/include/SFML/System/Time.hpp \
           SFML-2.0_1-17-13/include/SFML/System/Utf.hpp \
           SFML-2.0_1-17-13/include/SFML/System/Vector2.hpp \
           SFML-2.0_1-17-13/include/SFML/System/Vector3.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/Context.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/ContextSettings.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/Event.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/Export.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/GlResource.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/Joystick.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/Keyboard.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/Mouse.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/VideoMode.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/Window.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/WindowHandle.hpp \
           SFML-2.0_1-17-13/include/SFML/Window/WindowStyle.hpp
SOURCES += src/Application.cpp \
		   src/libtarga.c \
		   src/main.cpp \
		   src/Camera.cpp \
		   src/Light.cpp \
		   src/RayTracer.cpp \
		   src/RenderParams.cpp \
		   src/Scene.cpp \
		   src/Shader.cpp \
		   src/Shapes.cpp \
		   src/stdafx.cpp \
		   src/Utility.cpp \
           src/GUI/QSFMLCanvas.cpp

