#version 430 core

// The Data about the Vertex (in World Space) //
in Vertex
{
	vec3 position;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
	vec2 tex_coord;
} in_vertex;


// The Data about the Camera //	
layout (std140, binding = 0) uniform CameraData
{
	mat4 projection;	 // The Projection Matrix.
	mat4 projection_inv;
	mat4 view;			 // The View Matrix
	mat4 view_inv;
	mat4 view_it;
};

layout(location = 0) uniform vec3 eye_position;


// The Data about the Model //	
layout (std140, binding = 1) uniform ModelData
{
	mat4 model;		// The Model Matrix.
	mat4 model_inv;
	mat4 model_it;
};

layout (std140, binding = 2) uniform MaterialData
{
	vec4 ambient;	 // Material Color
	vec4 diffuse;
	vec4 specular;
	float shininess; // Material Surface Properties
	float roughness;
	float alpha;
};

// Texture //
layout(location = 1) uniform bool has_diffuse_texture;
layout (binding = 0) uniform sampler2D diffuse_texture;

// Texture //
layout(location = 2) uniform bool has_normal_texture;
layout (binding = 1) uniform sampler2D normal_texture;


// The Data about the Lights //	
struct LightData
{
	vec4 position;	  // The Position of the Light (+ w, which decided between directional and point light)
	vec4 attenuation; // The Light Attenuation + Radius
	vec4 ambient;	  // The Light Color
	vec4 diffuse;
	vec4 specular;
};

layout(std430, binding = 3) buffer LightBuffer
{
    LightData lights[];
};

layout(location = 3) uniform uint lights_count;
layout(location = 4) uniform vec3 global_ambient;

layout(location = 5) uniform bool use_alpha;
layout(location = 6) uniform vec3 ball_position;

layout (binding = 2) uniform sampler2D shadow_texture;
layout(location = 7) uniform mat4 light_view;
layout(location = 8) uniform mat4 light_projection;


// The Final Color of the Fragment //
layout(location = 0) out vec4 final_color;


void main()
{
	vec3 N = normalize(in_vertex.normal);
	vec3 V = normalize(eye_position - in_vertex.position);
	
	if (has_normal_texture)
	{
		vec3 T = normalize(in_vertex.tangent);
		vec3 B = normalize(in_vertex.bitangent);

		vec3 n = texture(normal_texture, in_vertex.tex_coord).rgb * 2.0 - 1.0;
		N = normalize(T * n.x + B * n.y + N * n.z);
	}

	vec3 amb = vec3(0.0f);
	vec3 dif = vec3(0.0f);
	vec3 spe = vec3(0.0f);

	for (int i = 0; i < lights_count; i++)
	{
		vec3 L = normalize(lights[i].position.xyz - lights[i].position.w * in_vertex.position);
		vec3 R = normalize(reflect(-L, N));

		float a = 1.0f;
		float d = max(dot(N, L), 0.0);
		float s = (dot(N, L) > 0.0f) ? roughness * pow(max(dot(V, R), 0.0f), shininess) : 0.0f;

		float atten_factor = 1.0f;

		if (lights[i].position.w != 0.0f)
		{
			float constant = lights[i].attenuation.x;
			float linear = lights[i].attenuation.y;
			float quadratic = lights[i].attenuation.z;
			float falloff = max(distance(lights[i].position.xyz, in_vertex.position) - lights[i].attenuation.w, 0.0f);

			atten_factor = 1.0f / (constant + linear * falloff + quadratic * pow(falloff, 2));
		}

		amb += a * lights[i].ambient.xyz * atten_factor;
		dif += d * lights[i].diffuse.xyz * atten_factor;
		spe += s * lights[i].specular.xyz * atten_factor;
	}

	vec3 final_ambient = ambient.xyz;
	vec3 final_diffuse = diffuse.xyz;
	vec3 final_specular = specular.xyz;

	vec4 clip_space = projection * view * vec4(in_vertex.position, 1.0f);
	vec3 screen_space = clip_space.xyz / clip_space.w;
	float final_alpha;
	
	if (use_alpha)
	{
		vec3 camera_ball_direction = ball_position - eye_position;
		vec3 camera_fragment_direction = in_vertex.position - eye_position;

		float angle_cos = 0.825f / length(eye_position.xyz);

		if (dot(vec2(0.0f, 1.0f), normalize(ball_position.xz)) < angle_cos && dot(vec2(0.0f, 1.0f), normalize(in_vertex.position.xz)) < angle_cos)
		{
			if (length(in_vertex.position.xz) < length(ball_position.xz))
			{
				final_alpha = max(0.0f, 1.0f - 200.0f * (dot(normalize(camera_ball_direction), normalize(camera_fragment_direction)) - 0.995f));
			}
			else
			{
				final_alpha = 1.0f;
			}
		}
		else if (dot(vec2(0.0f, 1.0f), normalize(ball_position.xz)) < angle_cos && dot(vec2(0.0f, 1.0f), normalize(in_vertex.position.xz)) >= angle_cos)
		{
			final_alpha = max(0.0f, 1.0f - 200.0f * (dot(normalize(camera_ball_direction), normalize(camera_fragment_direction)) - 0.995f));
		}
		else if (dot(vec2(0.0f, 1.0f), normalize(ball_position.xz)) >= angle_cos && dot(vec2(0.0f, 1.0f), normalize(in_vertex.position.xz)) < angle_cos)
		{
			final_alpha = 1.0f;
		}
		else if (dot(vec2(0.0f, 1.0f), normalize(ball_position.xz)) >= angle_cos && dot(vec2(0.0f, 1.0f), normalize(in_vertex.position.xz)) >= angle_cos)
		{
			if (length(in_vertex.position.xz) > length(ball_position.xz))
			{
				final_alpha = max(0.0f, 1.0f - 200.0f * (dot(normalize(camera_ball_direction), normalize(camera_fragment_direction)) - 0.995f));
			}
			else
			{
				final_alpha = 1.0f;
			}
		}
	}
	else
	{
		final_alpha = 1.0f;
	}

	if (has_diffuse_texture)
	{
		final_ambient = texture(diffuse_texture, in_vertex.tex_coord).xyz;
		final_diffuse = texture(diffuse_texture, in_vertex.tex_coord).xyz;
	}

	vec4 shadow_position_cs = light_projection * light_view * vec4(in_vertex.position, 1.0f);
	vec3 shadow_position_ss = 0.5f * shadow_position_cs.xyz / shadow_position_cs.w + 0.5f;
	float shadow = 0.0f;

	vec3 light_direction = normalize(lights[0].position.w * in_vertex.position - lights[0].position.xyz);
	float bias = max(0.0001f * (1.0f - dot(N, light_direction)), 0.00001f);

	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			float depth = textureOffset(shadow_texture, shadow_position_ss.xy, ivec2(i, j)).r;

			if (depth < shadow_position_ss.z - bias)
			{
				shadow += 1.0f;
			}
		}
	}

	shadow /= 25.0f;

	final_color = vec4((1.0f - shadow * 0.5f) * (final_ambient * amb + final_diffuse * dif + final_specular * spe), final_alpha);
}