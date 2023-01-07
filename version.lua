version = {
    file_names = {
        _global = {
            major = "VERSION/GLOBAL/MAJOR",
            minor = "VERSION/GLOBAL/MINOR",
            path = "VERSION/GLOBAL/PATH"
        },
        _graphics = {
            major = "VERSION/GRAPHICS/MAJOR",
            minor = "VERSION/GRAPHICS/MINOR",
            path = "VERSION/GRAPHICS/PATH"
        },
        _physics = {
            major = "VERSION/PHYSICS/MAJOR",
            minor = "VERSION/PHYSICS/MINOR",
            path = "VERSION/PHYSICS/PATH"
        },
        _utility = "VERSION/UTILITY"
    },

    _global = {
        major = 0,
        minor = 0,
        path = 0
    },
    _graphics = {
        major = 0,
        minor = 0,
        path = 0
    },
    _physics = {
        major = 0,
        minor = 0,
        path = 0
    },
    _utility = 0,

    formated = {
        _global = 0,
        _graphics = 0,
        _physics = 0,
        version = 0
    },

    message = 0,
}



function read_num_from_file(file_name)
    local file = io.open(file_name, "r")

    local num = file:read("*n")

    file:close()
    return num
end

function write_num_to_file(file_name, num)
    local file = io.open(file_name, "w")

    file:write(num)

    file:close()
end



function version:load_physics_version()
    self._physics.major = read_num_from_file(self.file_names._physics.major)
    self._physics.minor = read_num_from_file(self.file_names._physics.minor)
    self._physics.path = read_num_from_file(self.file_names._physics.path)
end

function version:load_graphics_version()
    self._graphics.major = read_num_from_file(self.file_names._graphics.major)
    self._graphics.minor = read_num_from_file(self.file_names._graphics.minor)
    self._graphics.path = read_num_from_file(self.file_names._graphics.path)
end

function version:load_global_version()
    self._global.major = read_num_from_file(self.file_names._global.major)
    self._global.minor = read_num_from_file(self.file_names._global.minor)
    self._global.path = read_num_from_file(self.file_names._global.path)
end

function version:load_utility_version()
    local file = io.open(self.file_names._utility, "r")

    self._utility = file:read("*a")

    file:close()
end

function version:load_version()
    self:load_physics_version()
    self:load_graphics_version()
    self:load_global_version()
    self:load_utility_version()
end



function version:upload_physics_version()
    write_num_to_file(self.file_names._physics.major, self._physics.major)
    write_num_to_file(self.file_names._physics.minor, self._physics.minor)
    write_num_to_file(self.file_names._physics.path, self._physics.path)
end

function version:upload_graphics_version()
    write_num_to_file(self.file_names._graphics.major, self._graphics.major)
    write_num_to_file(self.file_names._graphics.minor, self._graphics.minor)
    write_num_to_file(self.file_names._graphics.path, self._graphics.path)
end

function version:upload_global_version()
    write_num_to_file(self.file_names._global.major, self._global.major)
    write_num_to_file(self.file_names._global.minor, self._global.minor)
    write_num_to_file(self.file_names._global.path, self._global.path)
end

function version:upload_utility_version()
    local file = io.open(self.file_names._utility, "w")

    file:write(self._utility)

    file:close()
end

function version:upload_version()
    self:upload_physics_version()
    self:upload_graphics_version()
    self:upload_global_version()
    self:upload_utility_version()
end



function version:format_physics_version()
    self.formated._physics = "p" .. self._physics.major .. "." .. self._physics.minor .. "." .. self._physics.path
end

function version:format_graphics_version()
    self.formated._graphics = "g" .. self._graphics.major .. "." .. self._graphics.minor .. "." .. self._graphics.path
end

function version:format_global_version()
    self.formated._global = "v" .. self._global.major .. "." .. self._global.minor .. "." .. self._global.path
end

function version:format_version()
    self:format_physics_version()
    self:format_graphics_version()
    self:format_global_version()

    if self._utility == "0" then
        self.formated.version = self.formated._global .. "-" .. self.formated._graphics .. "-" .. self.formated._physics
    else
        self.formated.version = self.formated._global .. "-" .. self.formated._graphics .. "-" .. self.formated._physics .. "-" .. self._utility
    end
end



function version:print_physics_version()
    io.write(self.formated._physics)
end

function version:print_graphics_version()
    io.write(self.formated._graphics)
end

function version:print_global_version()
    io.write(self.formated._global)
end

function version:print_version()
    self:format_version()
    io.write(self.formated.version)
end



function version:change_version(format, type)
    if format == "p" then
        self._global.minor = self._global.minor + 1
        if type == "major" then
            self._physics.major = self._physics.major + 1
            self._physics.minor = 0
            self._physics.path = 0
        elseif type == "minor" then
            self._physics.minor = self._physics.minor + 1
            self._physics.path = 0
        elseif type == "path" then
            self._physics.path = self._physics.path + 1
        end
    elseif format == "g" then
        self._global.minor = self._global.minor + 1
        if type == "major" then
            self._graphics.major = self._graphics.major + 1
            self._graphics.minor = 0
            self._graphics.path = 0
        elseif type == "minor" then
            self._graphics.minor = self._graphics.minor + 1
            self._graphics.path = 0
        elseif type == "path" then
            self._graphics.path = self._graphics.path + 1
        end
    elseif format == "v" then
        if type == "major" then
            self._global.major = self._global.major + 1
            self._global.minor = 0
            self._global.path = 0
        elseif type == "minor" then
            self._global.minor = self._global.minor + 1
            self._global.path = 0
        elseif type == "path" then
            self._global.path = self._global.path + 1
        end
    end
end



function version:git_tag()
    os.execute("git add .")
    os.execute("git commit -m \"pre-version commit " .. self.formated.version .. "\"")
    os.execute("git tag -a " .. self.formated.version .. " -m \"" .. self.message .. "\"")
end



function main()
    version:load_version()
    version:format_version()

    while true do
        io.write("Current version is: ")
        version:print_version()
        io.write("\n")

        io.write("Text the format(v/g/p/e): ")
        local format = io.read()

        if format == "v" or format == "g" or format == "p" then
            io.write("Text the type of version you want to increment(major/minor/path): ")
            local type = io.read()

            version:change_version(format, type)
        elseif format == "e" then
            io.write("Do you want to tag?(y/n): ")
            local is_tag = io.read()

            if is_tag == "y" then
                io.write("Text the message: ")
                local message = io.read()

                version.message = message

                version:git_tag()
            else
                break
            end
        end
    end

    version:upload_version()
end

main()