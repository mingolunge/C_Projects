#version 330

out vec4 finalColor;

uniform float time;
uniform vec2 resolution;
uniform vec2 mouse;

vec3 palette(float t){
	vec3 a = vec3(0.500, 0.500, 0.500);
	vec3 b = vec3(-0.802, 0.500, 0.500);
	vec3 c = vec3(1.000, 1.000, 1.000);
	vec3 d = vec3(0.000, 0.333, 0.667);
	
	return a + b * cos(6.28318 * (c + t * d) );
}

void main()
{
    vec3 c = vec3(0.0);
    float l;
    float t = time;
	vec2 p = gl_FragCoord.xy / resolution.xy *2. - .1;
	vec2 p0 = p;
	p.x *= resolution.x / resolution.y;
	p = (fract(p * 2) -.5);
	// p.x -= mouse.x;
	// p.y += mouse.y;
	l = length(p);
	vec3 col = palette(l + abs(sin(time)));
	l = sin(l*8 + time) / 8;
	l = abs(l);
	
	l = 0.02 / l;

	// for (int i = 0; i < 3; ++i) {
	// 	t+=.1;
	// 	c[i] = 0.02 / abs(sin(l * 8. + t)/4.) - (abs(mouse.x / 20)) +.2;
	// }
    finalColor = vec4(col, 1.);
}
