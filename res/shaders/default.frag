#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 textureCoord;

uniform vec4 inputColor;
uniform sampler2D textureData;

uniform bool useTexture;
uniform bool useInputColor;
uniform bool useRainbow;

void main() {
    if (useTexture && useInputColor) {
        FragColor = texture(textureData, textureCoord) * inputColor;
    } else if(useTexture && useRainbow) {
        FragColor = texture(textureData, textureCoord) * vec4(color, 1);
    } else if(useTexture) {
        FragColor = texture(textureData, textureCoord);
    } else if(useInputColor) {
        FragColor = inputColor;
    } else {
        FragColor = vec4(color, 1.0);
    }
}
