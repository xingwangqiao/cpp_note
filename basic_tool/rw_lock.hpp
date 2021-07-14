#include <atomic>
#include <mutex>
#include <condition_variable>
namespace basic {
class rw_lock_t {
public:
    rw_lock_t() : is_writing_(false), writer_cnt_(0), reader_cnt_(0){ }
    void wlock() {
        std::unique_lock<std::mutex> lock(m_mutex_);
        ++writer_cnt_;
        writer_cond_.wait(lock, [this]{
            return !reader_cnt_ && !is_writing_;
        });
        is_writing_ = true;
    }

    bool try_wlock() {
        std::unique_lock<std::mutex> lock(m_mutex_);
        if(reader_cnt_ != 0 || is_writing_) {
            return false;
        }
        ++writer_cnt_;
        is_writing_ = true;
        return true;
    }

    void release_wlock() {
        std::unique_lock<std::mutex> lock(m_mutex_);
        is_writing_ = false;
        if((--writer_cnt_)){
            writer_cond_.notify_one();
        }
        else {
            reader_cond_.notify_all();
        }
    }

    void rlock() {
        std::unique_lock<std::mutex> lock(m_mutex_);
        reader_cond_.wait(lock, [this]{
            return !writer_cnt_;
        });
        ++reader_cnt_;
    }

    bool try_rlock() {
        std::unique_lock<std::mutex> lock(m_mutex_);
        if(!writer_cnt_) {
            return false;
        }
        ++reader_cnt_;
        return true;
    }

    void release_rlock() {
        std::unique_lock<std::mutex> lock(m_mutex_);
        if(!(--reader_cnt_)) {
            writer_cond_.notify_all();
        }
    }

private:
    std::mutex m_mutex_;
    std::atomic<bool> is_writing_;
    std::atomic<uint16_t> writer_cnt_;
    std::atomic<uint16_t> reader_cnt_;
    std::condition_variable writer_cond_;
    std::condition_variable reader_cond_;
};
} // namespace basic
