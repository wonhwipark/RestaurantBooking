#include "gmock/gmock.h"
#include "booking_scheduler.cpp"


using namespace testing;

class BookingScheduleFixture : public Test {
public:
	tm makeTime(int year, int month, int day, int hour, int minute) {
		tm time = { 0, minute, hour, day, month - 1, year - 1900, 0, 0, -1 };
		mktime(&time); // 나머지 tm 구조체 맴버값에 대해 자동으로 계산하여 채움
		return time;
	}

	static constexpr int UNDER_CAPACITY = 1;
	static constexpr int CAPACITY_PER_HOUR = 3;
	tm NOT_ON_THE_HOUR;
	Customer customer{ "Fake name", "010-1234-5678" };

protected:
	void SetUp() override {
		NOT_ON_THE_HOUR = makeTime(2021, 3, 26, 9, 0); // 2021년 3월 26일 9시 정각
	}
};

TEST_F(BookingScheduleFixture, 예약은정시에만가능하다정시가아닌경우예약불가) {
	//arrange
	Schedule* schedule = new Schedule{ NOT_ON_THE_HOUR, 1, customer };
	BookingScheduler bookingScheduler{ CAPACITY_PER_HOUR };
	//act
	EXPECT_THROW({
	bookingScheduler.addSchedule(schedule);
		}, std::runtime_error);
	//assert
	//expected runtime exception
}

TEST(BookingSchedulerTest, 예약은정시에만가능하다정시가아닌경우예약불가) {

}

TEST(BookingSchedulerTest, 예약은정시에만가능하다정시인경우예약가능) {

}

TEST(BookingSchedulerTest, 시간대별인원제한이있다같은시간대에Capacity초과할경우예외발생) {

}

TEST(BookingSchedulerTest, 시간대별인원제한이있다같은시간대가다르면Capacity차있어도스케쥴추가성공) {

}

TEST(BookingSchedulerTest, 예약완료시SMS는무조건발송) {

}

TEST(BookingSchedulerTest, 이메일이없는경우에는이메일미발송) {

}

TEST(BookingSchedulerTest, 이메일이있는경우에는이메일발송) {

}

TEST(BookingSchedulerTest, 현재날짜가일요일인경우예약불가예외처리) {

}

TEST(BookingSchedulerTest, 현재날짜가일요일이아닌경우예약가능) {

}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}