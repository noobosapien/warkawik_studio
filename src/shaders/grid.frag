precision mediump float;

uniform float u_vpw; 
uniform float u_vph; 

uniform vec2 u_offset; 
uniform vec2 u_pitch; 

void main() {
  float lX = gl_FragCoord.x / u_vpw;
  float lY = gl_FragCoord.y / u_vph;

  float scaleFactor = 10000.0;

  float offX = (scaleFactor * u_offset[0]) + gl_FragCoord.x;
  float offY = (scaleFactor * u_offset[1]) + (1.0 - gl_FragCoord.y);

  if (int(mod(offX, u_pitch[0])) == 0 ||
      int(mod(offY, u_pitch[1])) == 0) {
    gl_FragColor = vec4(0.0, 0.7098, 0.8314, 0.5);
  } else {
    // gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    discard;
  }
}