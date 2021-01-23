#include <mutex>
#include <utility>
#include <vector>
#include <condition_variable>

class CategoriesMutex {
public:
    explicit CategoriesMutex(std::vector<int> category_sizes) :
            category_sizes_{std::move(category_sizes)}, current_category_{-1}, count_{0} {}

    enum LockStatus {
        LOCK_SUCCESS = 0,
        THREADS_COUNT_EXCEEDED = 1,
        ANOTHER_CATEGORY = 2
    };

    class LockProxy {
    public:
        LockProxy(CategoriesMutex &mutex, LockStatus status) : mutex_{mutex}, status{status} {}

        ~LockProxy() {
            if (status == LOCK_SUCCESS) {
                mutex_.unlock();
            }
        }

        explicit operator bool() const {
            return status == LOCK_SUCCESS;
        }

        const LockStatus status;
    private:
        CategoriesMutex &mutex_;
    };

    LockProxy lock(size_t category) {
        std::unique_lock lock(internal_);
        cv.wait(lock, [&] { return try_lock_unsafe(category) == LOCK_SUCCESS; });
        return LockProxy(*this, LOCK_SUCCESS);
    }

    LockProxy try_lock(int category) {
        std::lock_guard lock(internal_);
        return LockProxy(*this, try_lock_unsafe(category));
    }

private:
    enum UnlockStatus {
        UNLOCK_SUCCESS = 0,
        ALREADY_UNLOCKED = 1
    };

    LockStatus try_lock_unsafe(int category) {
        if (current_category_ != -1 && category != current_category_) {
            return ANOTHER_CATEGORY;
        }

        if (count_ == category_sizes_[category]) {
            return THREADS_COUNT_EXCEEDED;
        }

        current_category_ = category;
        ++count_;
        return LOCK_SUCCESS;
    }

    UnlockStatus unlock() {
        std::unique_lock lock(internal_);
        if (count_ == 0) {
            return ALREADY_UNLOCKED;
        }
        --count_;
        if (count_ == 0) {
            current_category_ = -1;
        }

        lock.unlock();
        cv.notify_all();
        return UNLOCK_SUCCESS;
    }

    int current_category_;
    int count_;
    const std::vector<int> category_sizes_;
    std::mutex internal_;
    std::condition_variable cv;
};

int main() {
    CategoriesMutex mutex({1, 3, 5});
    if (auto guard = mutex.try_lock(1); guard) {
        // critical section
    }
}
