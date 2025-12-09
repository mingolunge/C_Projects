#version 330

uniform float time;
uniform vec2 resolution;

out vec4 FragColor;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution;
    float v = 0.5 + 0.5 * sin(time + uv.x * 10.0 + uv.y * 10.0);
    FragColor = vec4(vec3(v), 1.0);
}
