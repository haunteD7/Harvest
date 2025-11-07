#pragma once

#include <string>

#include "gl_extra.h"

#include "log.h"
#include "types.h"

class ShaderProgram;

class Shader
{
public:
    enum class Type : u8
    {
        Vertex,
        Fragment,

        Count
    };
    static const char *get_shader_type_char(Type type)
    {
        switch (type)
        {
        case Type::Fragment:
        {
            return "Fragment";
        }
        case Type::Vertex:
        {
            return "Vertex";
        }
        }
        return "Unknown";
    }
    enum class State : u8
    {
        Created,
        SourceLoaded,
        Compiled,
        Error
    };
    static const char *get_shader_state_char(State state)
    {
        switch (state)
        {
        case Shader::State::Created:
        {
            return "Created";
        }
        case Shader::State::SourceLoaded:
        {
            return "Source loaded";
        }
        case Shader::State::Compiled:
        {
            return "Compiled";
        }
        case Shader::State::Error:
        {
            return "Error";
        }
        }
    }
    Shader() = delete;
    ~Shader();
    Shader(Type type);
    Shader(Type type, const char *source_text);
    bool compile();

    void set_source(const char *source_text);

    GLuint get_id() const;
    State get_state() const;

    void attach_to_program(const ShaderProgram &shader_program);
    void detach_from_program();

private:
    GLuint _id;
    GLuint _program_id_attached_to;

    Type _type;
    State _state;
};

class ShaderProgram
{
public:
    enum class State : u8
    {
        Created,
        Linked,
        Error,
    };

    ShaderProgram();
    ~ShaderProgram();

    GLuint get_id() const;

    void attach_shader(Shader &shader);
    void detach_shader(Shader &shader);
    bool link();
    void use();

private:
    GLuint _id;
    State _state;
};