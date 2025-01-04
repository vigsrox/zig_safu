const std = @import("std");

pub fn build(b: *std.Build) void { 
    const target = b.standardTargetOptions(.{});

    const optimize = b.standardOptimizeOption(.{});

    //const hw_id_file = b.option([]const u8,"SAFU_HARDWAREID_FILE","hardware id file") orelse "/etc/machine-id";
    //const hw_id_max_len = b.option([]const u8, "SAFU_HARDWAREID_MAX_LENGTH","hardware is max length") orelse "2048";
    //const hw_id_def_val = b.option([]const u8, "SAFU_HARDWAREID_DEFAULT_VALUE", "hardware id default value") orelse "INVALID";
    //const hw_id_en_prefix = b.option([]const u8,"SAFU_HARDWAREID_ENVIRONMENT_PREFIX","hardware id env prefix") orelse "SAFU_HARDWAREID_";

    //const safu_log_prefix = b.option([]const u8,"SAFU_LOG_PREFIX", "safu log prefix") orelse "[SAFU] ";


    const safu_lib = b.addSharedLibrary(.{
        .name = "safu_z",
        .target = target,
        .optimize = optimize,
    });

    const lib_src_files = [_][]const u8 {
      "src/safu/private/common.c",
      "src/safu/private/json.c",
      "src/safu/private/log.c",
      "src/safu/private/ringbuffer.c",
      "src/safu/private/time.c",
      "src/safu/private/vector.c",
    };

    const cflags = [_][]const u8{
        "-std=c17",
        "-Wshadow",
        "-Wall",
        "-Wextra",
        "-pedantic",
        "-D_DEFAULT_SOURCE",
        "-Og",
        "-g3",
        "-DDEBUG",
        "-fno-omit-frame-pointer"
    };

    safu_lib.addCSourceFiles(. { .files = &lib_src_files, .flags = &cflags });
    safu_lib.root_module.addCMacro("SAFU_HARDWAREID_FILE", "\"" ++ "/etc/machine-id" ++ "\"" );
    safu_lib.root_module.addCMacro("SAFU_HARDWAREID_MAX_LENGTH", "2048");
    safu_lib.root_module.addCMacro("SAFU_HARDWAREID_DEFAULT_VALUE", "\"" ++ "INVALID" ++ "\"");
    safu_lib.root_module.addCMacro("SAFU_HARDWAREID_ENVIRONMENT_PREFIX", "\"" ++ "SAFU_HARDWAREID_" ++ "\"");
    safu_lib.root_module.addCMacro("SAFU_LOG_PREFIX", "\"" ++ "[SAFU] " ++ "\"");
    safu_lib.linkSystemLibrary("json-c");
    safu_lib.addIncludePath(b.path("src/safu/public"));
    safu_lib.addIncludePath(b.path("src/safu/interface"));
    safu_lib.installHeadersDirectory(b.path("src/safu/public/safu"), "", .{});
    safu_lib.installHeadersDirectory(b.path("src/safu/interface/safu"), "", .{});
    safu_lib.linkLibC();

    b.installArtifact(safu_lib);

}
