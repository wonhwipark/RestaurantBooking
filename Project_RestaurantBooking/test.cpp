#include "gmock/gmock.h"
#include "booking_scheduler.cpp"


using namespace testing;

class BookingScheduleFixture : public Test {
public:
	tm makeTime(int year, int month, int day, int hour, int minute) {
		tm time = { 0, minute, hour, day, month - 1, year - 1900, 0, 0, -1 };
		mktime(&time); // ������ tm ����ü �ɹ����� ���� �ڵ����� ����Ͽ� ä��
		return time;
	}

	static constexpr int UNDER_CAPACITY = 1;
	static constexpr int CAPACITY_PER_HOUR = 3;
	tm NOT_ON_THE_HOUR;
	Customer customer{ "Fake name", "010-1234-5678" };

protected:
	void SetUp() override {
		NOT_ON_THE_HOUR = makeTime(2021, 3, 26, 9, 0); // 2021�� 3�� 26�� 9�� ����
	}
};

TEST_F(BookingScheduleFixture, ���������ÿ��������ϴ����ð��ƴѰ�쿹��Ұ�) {
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

TEST(BookingSchedulerTest, ���������ÿ��������ϴ����ð��ƴѰ�쿹��Ұ�) {

}

TEST(BookingSchedulerTest, ���������ÿ��������ϴ������ΰ�쿹�డ��) {

}

TEST(BookingSchedulerTest, �ð��뺰�ο��������ִٰ����ð��뿡Capacity�ʰ��Ұ�쿹�ܹ߻�) {

}

TEST(BookingSchedulerTest, �ð��뺰�ο��������ִٰ����ð��밡�ٸ���Capacity���־�������߰�����) {

}

TEST(BookingSchedulerTest, ����Ϸ��SMS�¹����ǹ߼�) {

}

TEST(BookingSchedulerTest, �̸����̾��°�쿡���̸��Ϲ̹߼�) {

}

TEST(BookingSchedulerTest, �̸������ִ°�쿡���̸��Ϲ߼�) {

}

TEST(BookingSchedulerTest, ���糯¥���Ͽ����ΰ�쿹��Ұ�����ó��) {

}

TEST(BookingSchedulerTest, ���糯¥���Ͽ����̾ƴѰ�쿹�డ��) {

}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}