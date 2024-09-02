const std = @import("std");
const Mutex = @import("mutex.zig").Mutex;

var m = Mutex{};
var m_std = std.Thread.Mutex{};

var counter: u32 = 0;

const threadCount = 30;

fn increment(threadIdx: usize) void {
    for (0..10000) |_| {
        m.lock();
        // m_std.lock();
        counter += 1;
        std.debug.print("Thread {}: Incrementing to {}\n", .{ threadIdx, counter });
        m.unlock();
        // m_std.unlock();
    }
}

pub fn main() !void {
    var threads: [threadCount]std.Thread = undefined;
    for (threads) |i| {
        threads[i] = try std.Thread.spawn(.{}, increment, .{i});
    }

    for (threads) |thread| {
        thread.join();
    }

    std.debug.print("Counter: {}\n", .{counter});
}
