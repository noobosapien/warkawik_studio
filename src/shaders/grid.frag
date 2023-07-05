precision mediump float;

uniform vec2 u_offset; 
uniform vec2 u_pitch; 

void main() {

  float offX = (u_offset[0]) + gl_FragCoord.x;
  float offY = (u_offset[1]) + gl_FragCoord.y;

  if (int(mod(offX, u_pitch[0])) == 0 || 
      int(mod(offY, u_pitch[1])) == 0) {

        if (int (offX) == 300 || int(offY) == 300){
          gl_FragColor = vec4(0.0, 0.7098, 0.8314, 1.);
        }else{
          gl_FragColor = vec4(0.0, 0.7098, 0.8314, 0.4);
      }
    
  } else {
    discard;
  }
}