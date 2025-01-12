#include <iostream>
#include <vector>
#include <stdexcept> 

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
   
    if (nums.size() < 2 || nums.size() > 10000) {
        throw std::invalid_argument("Array size must be between 2 and 10^4.");
    }
    for (int num : nums) {
        if (num < -1000000000 || num > 1000000000) {
            throw std::invalid_argument("Array elements must be between -10^9 and 10^9.");
        }
    }
    if (target < -1000000000 || target > 1000000000) {
        throw std::invalid_argument("Target value must be between -10^9 and 10^9.");
    }

   
    for (int i = 0; i < nums.size(); ++i) {
        
        for (int j = i + 1; j < nums.size(); ++j) {
            
            if (nums[i] + nums[j] == target) {
                
                return {i, j};
            }
        }
    }
   
    return {};
}

int main() {
    try {
        // Example usage
        std::vector<int> nums1 = {2, 7, 11, 15};
        int target1 = 9;
        std::vector<int> result1 = twoSum(nums1, target1);
        std::cout << "Output: [" << result1[0] << ", " << result1[1] << "]" << std::endl;

        std::vector<int> nums2 = {3, 2, 4};
        int target2 = 6;
        std::vector<int> result2 = twoSum(nums2, target2);
        std::cout << "Output: [" << result2[0] << ", " << result2[1] << "]" << std::endl;

        std::vector<int> nums3 = {3, 3};
        int target3 = 6;
        std::vector<int> result3 = twoSum(nums3, target3);
        std::cout << "Output: [" << result3[0] << ", " << result3[1] << "]" << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
