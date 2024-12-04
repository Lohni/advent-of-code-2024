//! By convention, main.zig is where your main function lives in the case that
//! you are building an executable. If you are making a library, the convention
//! is to delete this file and start with root.zig instead.
const std = @import("std");

pub fn main() !void {
    std.log.info("Advent of code - Day 1", .{});
    const allocator = std.heap.page_allocator;

    std.log.info("Read List", .{});
    const list_input_file = "resource/day1-list.txt";

    var firstNumbers = std.AutoHashMap(i32, void).init(allocator);
    defer firstNumbers.deinit();

    var secondNumbers = std.AutoHashMap(i32, void).init(allocator);
    defer secondNumbers.deinit();

    //Open file
    const file = try std.fs.cwd().openFile(list_input_file, .{});
    defer file.close();

    var buffer: [1048]u8 = undefined;
    const reader = file.reader();

    while (reader.readUntilDelimiterOrEof(&buffer, '\n')) |bytes_read| {
        if (bytes_read == null) break;

        var firstNumber = false;
        var secondNumber = false;

        var lineChunks = std.mem.splitSequence(u8, &buffer, " ");
        while (lineChunks.next()) |chunk| {
            if (chunk.len > 0) {
                const number = try std.fmt.parseInt(i32, chunk, 10);
                if (!firstNumber) {
                    try firstNumbers.put(number, {});
                    firstNumber = true;
                } else if (!secondNumber) {
                    try secondNumbers.put(number, {});
                    secondNumber = true;
                } else break;
            }
        }
    } else |err| {
        std.log.info("{s}", err);
    }

    const firstUniqueNumbers: []i32 = try allocator.alloc(i32, firstNumbers.count());
    defer allocator.free(firstUniqueNumbers);
    //const secondUniqueNumbers: [][]const u8 =  allocator.alloc([]const u8, firstNumbers.count());

    defer {
        var firstIter = firstNumbers.keyIterator();
        var i: u16 = 0;
        var next = firstIter.next();
        while (next) |key| {
            firstUniqueNumbers[i] = key.*;
            i += 1;
            next = firstIter.next();
        }
    }

    std.mem.sort(i32, firstUniqueNumbers, {}, std.sort.asc(i32));
    //std.mem.sort(u2, secondUniqueNumbers, {}, std.sort.asc([]u8));

    for (0..firstUniqueNumbers.len) |x| {
        std.log.info("{d}:{s}}", .{ firstUniqueNumbers[x], "test" });
    }
}
