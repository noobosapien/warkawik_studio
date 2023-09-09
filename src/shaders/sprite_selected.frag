precision highp float;

varying vec2 v_fragTexCoord;

uniform sampler2D uTexture;

void main()
{
	float left = texture2D(uTexture, v_fragTexCoord + vec2(-0.05, 0)).a;
	float right = texture2D(uTexture, v_fragTexCoord + vec2(0.05, 0)).a;
	float up = texture2D(uTexture, v_fragTexCoord + vec2(0, 0.05)).a;
	float down = texture2D(uTexture, v_fragTexCoord + vec2(0, -0.05)).a;

	float sum = left + right + up + down;
	float outline = min(sum, 1.0);

	vec4 color = texture2D(uTexture, v_fragTexCoord);

	gl_FragColor = mix(color, vec4(1.0), outline - color.a);
	// gl_FragColor = texture2D(uTexture, v_fragTexCoord);
}