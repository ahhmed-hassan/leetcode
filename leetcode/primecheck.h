#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <span>
#include <print>
namespace medianOfTwoSortedArrays
{
	using namespace std;

	pair<size_t, size_t> get_median_indeicies(std::span<const int> range) {
		auto size = range.size();
		if (size == 0) {
			throw std::invalid_argument("NOOOO");
		}

		if (size % 2 == 0)
			return { size / 2 - 1,size / 2 };

		else
			return { size / 2,size / 2 };

	}


	double both_sizes_less_than_three(span<const int> nums1, span<const int> nums2) {
		vector<int> result{};
		result.resize(nums1.size() + nums2.size());
		std::ranges::merge(nums1, nums2, result.begin());
		auto [first, second] = get_median_indeicies(result);
		//cout << result[first] << ' ' << result[second];
		//cout << endl;
		return (result[first] + result[second]) / 2.0;
	}

	double one_size_is_two_or_less(span<const int> s1, span<const int> s2) {
		vector<int> medianContainer{};

		if (s1.size() <= 2) {
			swap(s1, s2);
		};
		auto [first, second] = get_median_indeicies(s1);
		medianContainer.insert(medianContainer.end(), s1.begin() + first - 1, s1.begin() + second + 1 + 1);
		return both_sizes_less_than_three(s2, medianContainer);
	}

	
	double median_of_two_big_sorted_spans(std::span<int const> spanWithSmallerMedian, std::span<int const> spanWithBigerMedian)
	{
		if (spanWithSmallerMedian.size() <= 2 && spanWithBigerMedian.size() <= 2) {
			return both_sizes_less_than_three(spanWithSmallerMedian, spanWithBigerMedian);
		}
		else if (spanWithSmallerMedian.size() <= 2 || spanWithBigerMedian.size() <= 2) {
			return one_size_is_two_or_less(spanWithSmallerMedian, spanWithBigerMedian);
		}
		auto smallerMedianIndicies = get_median_indeicies(spanWithSmallerMedian);
		auto biggerMedianIndicies = get_median_indeicies(spanWithBigerMedian);
		if ((spanWithSmallerMedian[smallerMedianIndicies.first] + spanWithSmallerMedian[smallerMedianIndicies.second]) >
			(spanWithBigerMedian[biggerMedianIndicies.first] + spanWithBigerMedian[biggerMedianIndicies.second]))
		{
			swap(smallerMedianIndicies, biggerMedianIndicies);
			swap(spanWithSmallerMedian, spanWithBigerMedian); 
		}
		auto minimalSharedCut = std::min(smallerMedianIndicies.first, biggerMedianIndicies.first); 
		return median_of_two_big_sorted_spans(spanWithSmallerMedian.last(spanWithSmallerMedian.size() - minimalSharedCut),
			spanWithBigerMedian.first(spanWithBigerMedian.size() - minimalSharedCut));



	}

	double MedianOfTwoSortedArrays(const vector<int>& nums1, const vector<int>& nums2) {
		if (nums1.size() <= 2 && nums2.size() <= 2) {
			return both_sizes_less_than_three(nums1, nums2);
		}
		else if (nums1.size() <= 2 || nums2.size() <= 2) {
			one_size_is_two_or_less(nums1, nums2);
		}
	}

}
//int main()
//{
//    std::vector<int> nums1{ 1,5,6,8,9,12,15,15,16 }, nums2{  };
//
//    std::cout << medianOfTwoSortedArrays:: MedianOfTwoSortedArrays(nums2, nums1);
//    //span<int> s{ nums1 };
//    //s[0] = 30;
//    //for (auto x : nums1) {
//    //    cout << x << ' ';
//    //}
//    return 0;
//}
