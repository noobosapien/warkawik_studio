precision highp float;

varying vec2 v_fragTexCoord;

uniform sampler2D uTexture;

void main()
{
	gl_FragColor = texture2D(uTexture, v_fragTexCoord);
}