#pragma once

#include <daxa/daxa.inl>

#define SHADER_GLOBALS_SLOT 0

#define MAX_SURFACE_RES_X 3840
#define MAX_SURFACE_RES_Y 2160

#define MAX_INSTANTIATED_MESHES 100000
#define MAX_MESHLET_INSTANCES 1000000
#define VISIBLE_ENTITY_MESHLETS_BITFIELD_SCRATCH 1000000
#define MAX_DRAWN_TRIANGLES (MAX_SURFACE_RES_X * MAX_SURFACE_RES_Y)
#define MAX_DRAWN_MESHES 100000
#define TRIANGLE_SIZE 12
#define WARP_SIZE 32
#define MAX_ENTITY_COUNT (1u << 20u)
#define MAX_MATERIAL_COUNT (1u << 8u)
#define MESH_SHADER_WORKGROUP_X 32
#define ENABLE_MESHLET_CULLING 1
#define ENABLE_TRIANGLE_CULLING 1
#define ENABLE_SHADER_PRINT_DEBUG 1
#define COMPILE_IN_MESH_SHADER 0

#if __cplusplus
#include <glm/glm.hpp>
#define glmsf32vec2 glm::vec2
#define glmsf32vec3 glm::vec3
#define glmsf32vec4 glm::vec4
#define glmsf32mat4 glm::mat4
#else
#define glmsf32vec2 daxa_f32vec2
#define glmsf32vec3 daxa_f32vec3
#define glmsf32vec4 daxa_f32vec4
#define glmsf32mat4 daxa_f32mat4x4
#endif 

#if __cplusplus
#define SHADER_ONLY(x)
#else
#define SHADER_ONLY(x) x
#endif

struct Settings
{
    daxa_u32vec2 render_target_size;
    daxa_f32vec2 render_target_size_inv;
    daxa_u32 enable_mesh_shader;
    daxa_u32 draw_from_observer;
    daxa_i32 observer_show_pass;
#if __cplusplus
    auto operator==(Settings const &other) const -> bool 
    {
        return std::memcmp(this, &other, sizeof(Settings)) == 0;
    }
    auto operator!=(Settings const &other) const -> bool
    {
        return std::memcmp(this, &other, sizeof(Settings)) != 0;
    }
    Settings()
        : render_target_size{ 16, 16 },
        render_target_size_inv{ 1.0f / this->render_target_size.x, 1.0f / this->render_target_size.y },
        enable_mesh_shader{ 0 },
        draw_from_observer{ 0 },
        observer_show_pass{ 0 }
    {
    }
#endif
};

struct GlobalSamplers
{
    daxa_SamplerId linear_clamp;
    daxa_SamplerId linear_repeat;
    daxa_SamplerId nearest_clamp;
};

struct CameraInfo
{
    glmsf32mat4 view;
    glmsf32mat4 proj;
    glmsf32mat4 view_proj;
    glmsf32vec3 pos;
    glmsf32vec3 up;
    glmsf32vec3 near_plane_normal;
    glmsf32vec3 left_plane_normal;
    glmsf32vec3 right_plane_normal;
    glmsf32vec3 top_plane_normal;
    glmsf32vec3 bottom_plane_normal;
};

#if DAXA_SHADER
#define my_sizeof(T) uint64_t(daxa_BufferPtr(T)(daxa_u64(0)) + 1)
#endif

#if defined(__cplusplus)
#define SHARED_FUNCTION inline
#define SHARED_FUNCTION_INOUT(X) X&
#else
#define SHARED_FUNCTION
#define SHARED_FUNCTION_INOUT(X) inout X
#endif

SHARED_FUNCTION daxa_u32 round_up_to_multiple(daxa_u32 value, daxa_u32 multiple_of)
{
    return ((value + multiple_of - 1) / multiple_of) * multiple_of;
}

SHARED_FUNCTION daxa_u32 round_up_div(daxa_u32 value, daxa_u32 div)
{
    return (value + div - 1) / div;
}

#define ENABLE_TASK_USES(STRUCT, NAME)

struct DrawIndexedIndirectStruct
{
    daxa_u32 index_count;
    daxa_u32 instance_count;
    daxa_u32 first_index;
    daxa_u32 vertex_offset;
    daxa_u32 first_instance;
};
DAXA_DECL_BUFFER_PTR(DrawIndexedIndirectStruct)

struct DrawIndirectStruct
{
    daxa_u32 vertex_count;
    daxa_u32 instance_count;
    daxa_u32 first_vertex;
    daxa_u32 first_instance;
};
DAXA_DECL_BUFFER_PTR(DrawIndirectStruct)

struct DispatchIndirectStruct
{
    daxa_u32 x;
    daxa_u32 y;
    daxa_u32 z;
};
DAXA_DECL_BUFFER_PTR(DispatchIndirectStruct)

#define BUFFER_COMPUTE_READ(NAME, TYPE) DAXA_TH_BUFFER_PTR(COMPUTE_SHADER_READ, daxa_BufferPtr(TYPE), NAME)
#define BUFFER_COMPUTE_WRITE(NAME, TYPE) DAXA_TH_BUFFER_PTR(COMPUTE_SHADER_WRITE, daxa_RWBufferPtr(TYPE), NAME)