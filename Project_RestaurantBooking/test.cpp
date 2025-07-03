#include "gmock/gmock.h"
#include "booking_scheduler.cpp"
#include "testable_mail_sender.cpp"
#include "testable_booking_scheduler.cpp"

using namespace testing;

class BookingItem : public Test {
protected:
	void SetUp() override {
		NOT_ON_THE_HOUR = getTime(2021, 3, 26, 9, 5);
		ON_THE_HOUR = getTime(2021, 3, 26, 9, 0);
		SUNDAY_ON_THE_HOUR = getTime(2021, 3, 28, 17, 0);
		MONDAY_ON_THE_HOUR = getTime(2024, 6, 3, 17, 0);
		bookingScheduler.setMailSender(&testableMailSender);
	}
public:
	tm getTime(int year, int mon, int day, int hour, int min) {
		tm result = { 0, min, hour, day, mon - 1, year - 1900, 0, 0, -1 };
		mktime(&result);
		return result;
	}
	tm NOT_ON_THE_HOUR;
	tm ON_THE_HOUR;
	tm MONDAY_ON_THE_HOUR;
	tm SUNDAY_ON_THE_HOUR;
	Customer CUSTOMER{ "Fake name", "010-1234-5678" };
	Customer CUSTOMER_WITH_MAIL{ "Fake Name", "010-1234-5678", "test@test.com" };
	const int UNDER_CAPACITY = 1;
	const int CAPACITY_PER_HOUR = 3;
	BookingScheduler bookingScheduler{ 3 };
	TestableMailSender testableMailSender;
};



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
		NOT_ON_THE_HOUR = makeTime(2021, 3, 26, 9, 1); // 2021�� 3�� 26�� 9�� ����
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

TEST_F(BookingItem, �̸����̾��°�쿡���̸��Ϲ̹߼�) {
	//arrange

	Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };

	//act
	bookingScheduler.addSchedule(schedule);
	//assert
	EXPECT_EQ(0, testableMailSender.getCountSendMailMethodIsCalled());
}

TEST_F(BookingItem, �̸������ִ°�쿡���̸��Ϲ߼�) {
	//arrange
	Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER_WITH_MAIL };
	//act
	bookingScheduler.addSchedule(schedule);
	//assert
	EXPECT_EQ(1, testableMailSender.getCountSendMailMethodIsCalled());
}


TEST_F(BookingItem, ���糯¥���Ͽ����ΰ�쿹��Ұ�����ó��) {
	//arrange
	BookingScheduler* bookingScheduler = new TestableBookingScheduler{ CAPACITY_PER_HOUR,SUNDAY_ON_THE_HOUR };
	try {
		//act
		Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER_WITH_MAIL };
		bookingScheduler->addSchedule(schedule);
		FAIL();
	}
	catch (std::runtime_error& e) {
		//assert
		EXPECT_EQ(string{ e.what() }, string{ "Booking system is not available on sunday" });
	}
}


TEST_F(BookingItem, ���糯¥���Ͽ����̾ƴѰ�쿹�డ��) {
	//arrange
	BookingScheduler* bookingScheduler = new TestableBookingScheduler{ CAPACITY_PER_HOUR, MONDAY_ON_THE_HOUR };
	//act
	Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER_WITH_MAIL };
	bookingScheduler->addSchedule(schedule);
	//assert
	EXPECT_EQ(true, bookingScheduler->hasSchedule(schedule));
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}