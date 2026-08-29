#include <vector>
#include <cstdint>
#include <algorithm>

class DynamicBitset {
private:
    std::vector<uint64_t> m_blocks;
    size_t m_size;

    // Helper to clear unused bits in the last block
    void cleanup_last_block() {
        //turn to 0
        if (m_size % 64 != 0 && !m_blocks.empty()) {
            m_blocks.back() = m_blocks.back() & ((1ULL << (m_size%64)) -1ULL);
        }
    }

public:
    DynamicBitset(size_t n = 0) : m_size(n) {
        // TODO: Initialize blocks
        int total_blocks = m_size/64 + (m_size%64==0?0:1);
        for(int i=0; i<total_blocks; i++){
            m_blocks.push_back(static_cast<uint64_t>(0));
        }
    }

    size_t size() const {
        return m_size;
    }

    void resize(size_t n) {
        // TODO: Resize blocks and update m_size
        int new_blocks = n/64 + (n%64==0?0:1);
        int cur_blocks= m_blocks.size();
        if(new_blocks > m_blocks.size()){
            for(int i=0; i<new_blocks - cur_blocks; i++){
                m_blocks.push_back(static_cast<uint64_t>(0));
            }
        }
        else{
            m_blocks.resize(new_blocks);
        }

        m_size = n;
        cleanup_last_block();
    }

    void set(size_t i, bool val) {
        // TODO: Set bit i to val
        if (i >= m_size) {
            return;
        }
        int m_index = i/64;
        int offset = i%64;

        if(val){
            //set to 1
            m_blocks[m_index] = m_blocks[m_index] | (1ULL << offset);
        }
        else{
            m_blocks[m_index] = m_blocks[m_index] & ~(1ULL << offset);
        }
    }

    bool get(size_t i) const {
        // TODO: Return bit i
        if (i >= m_size) {
            return false;
        }
        int m_index = i/64;
        int offset = i%64;
        return m_blocks[m_index] & (1ULL << offset);
    }

    void op_and(const DynamicBitset& other) {
        // TODO: In-place AND
        //other is smaller

        size_t common_blocks = std::min(m_blocks.size(), other.m_blocks.size());
        for(int i=0; i<common_blocks; i++){
            m_blocks[i] = m_blocks[i] & other.m_blocks[i];
        }
        for(int i = common_blocks; i<m_blocks.size(); i++){
            m_blocks[i] = 0ULL;
        }
        cleanup_last_block();
    }

    void op_or(const DynamicBitset& other) {
        // TODO: In-place OR
        size_t common_blocks = std::min(m_blocks.size(), other.m_blocks.size());
        for(int i = 0; i<common_blocks; i++){
            m_blocks[i] = m_blocks[i] | other.m_blocks[i];
        }
        cleanup_last_block();
    }

    void op_xor(const DynamicBitset& other) {
        // TODO: In-place XOR
        for(int i=0; i<m_blocks.size(); i++){
            m_blocks[i] = m_blocks[i] ^ other.m_blocks[i];
        }
        cleanup_last_block();
    }

    size_t popcount() const {
        // TODO: Use __builtin_popcountll
        
        size_t count{};
        for(int i=0; i<m_blocks.size(); i++){
            count += __builtin_popcountll(m_blocks[i]);
        }
        //unused bits in the last block are 0
        return count;
    }

    int64_t ffs() const {
        // TODO: Use __builtin_ctzll
        for(int i=0; i<m_blocks.size(); i++){
            if(m_blocks[i] != 0){
                return i*64 + __builtin_ctzll(m_blocks[i]);
            }
        }
        return -1;
    }
};