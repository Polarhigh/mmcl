#ifndef INullInterface_h__
#define INullInterface_h__
#include "DebugHelp.h"

#define NULL_INTERFACE_VERSION "NullInterface001"

#define MKNULL(n) int NullFunc##n(...){DbgMsg("NullFunc " #n " called");return 0;}
#define MKVNULL(n) virtual int NullFunc##n(...)=0;

class INullInterface:public IBaseInterface
{
public:
		MKVNULL(0)
		MKVNULL(1)
		MKVNULL(2)
		MKVNULL(3)
		MKVNULL(4)
		MKVNULL(5)
		MKVNULL(6)
		MKVNULL(7)
		MKVNULL(8)
		MKVNULL(9)
		MKVNULL(10)
		MKVNULL(11)
		MKVNULL(12)
		MKVNULL(13)
		MKVNULL(14)
		MKVNULL(15)
		MKVNULL(16)
		MKVNULL(17)
		MKVNULL(18)
		MKVNULL(19)
		MKVNULL(20)
		MKVNULL(21)
		MKVNULL(22)
		MKVNULL(23)
		MKVNULL(24)
		MKVNULL(25)
		MKVNULL(26)
		MKVNULL(27)
		MKVNULL(28)
		MKVNULL(29)
		MKVNULL(30)
		MKVNULL(31)
		MKVNULL(32)
		MKVNULL(33)
		MKVNULL(34)
		MKVNULL(35)
		MKVNULL(36)
		MKVNULL(37)
		MKVNULL(38)
		MKVNULL(39)
		MKVNULL(40)
		MKVNULL(41)
		MKVNULL(42)
		MKVNULL(43)
		MKVNULL(44)
		MKVNULL(45)
		MKVNULL(46)
		MKVNULL(47)
		MKVNULL(48)
		MKVNULL(49)
		MKVNULL(50)
		MKVNULL(51)
		MKVNULL(52)
		MKVNULL(53)
		MKVNULL(54)
		MKVNULL(55)
		MKVNULL(56)
		MKVNULL(57)
		MKVNULL(58)
		MKVNULL(59)
		MKVNULL(60)
		MKVNULL(61)
		MKVNULL(62)
		MKVNULL(63)
		MKVNULL(64)
		MKVNULL(65)
		MKVNULL(66)
		MKVNULL(67)
		MKVNULL(68)
		MKVNULL(69)
		MKVNULL(70)
		MKVNULL(71)
		MKVNULL(72)
		MKVNULL(73)
		MKVNULL(74)
		MKVNULL(75)
		MKVNULL(76)
		MKVNULL(77)
		MKVNULL(78)
		MKVNULL(79)
		MKVNULL(80)
		MKVNULL(81)
		MKVNULL(82)
		MKVNULL(83)
		MKVNULL(84)
		MKVNULL(85)
		MKVNULL(86)
		MKVNULL(87)
		MKVNULL(88)
		MKVNULL(89)
		MKVNULL(90)
		MKVNULL(91)
		MKVNULL(92)
		MKVNULL(93)
		MKVNULL(94)
		MKVNULL(95)
		MKVNULL(96)
		MKVNULL(97)
		MKVNULL(98)
		MKVNULL(99)
		MKVNULL(100)
		MKVNULL(101)
		MKVNULL(102)
		MKVNULL(103)
		MKVNULL(104)
		MKVNULL(105)
		MKVNULL(106)
		MKVNULL(107)
		MKVNULL(108)
		MKVNULL(109)
		MKVNULL(110)
		MKVNULL(111)
		MKVNULL(112)
		MKVNULL(113)
		MKVNULL(114)
		MKVNULL(115)
		MKVNULL(116)
		MKVNULL(117)
		MKVNULL(118)
		MKVNULL(119)
		MKVNULL(120)
		MKVNULL(121)
		MKVNULL(122)
		MKVNULL(123)
		MKVNULL(124)
		MKVNULL(125)
		MKVNULL(126)
		MKVNULL(127)
		MKVNULL(128)
		MKVNULL(129)
		MKVNULL(130)
		MKVNULL(131)
		MKVNULL(132)
		MKVNULL(133)
		MKVNULL(134)
		MKVNULL(135)
		MKVNULL(136)
		MKVNULL(137)
		MKVNULL(138)
		MKVNULL(139)
		MKVNULL(140)
		MKVNULL(141)
		MKVNULL(142)
		MKVNULL(143)
		MKVNULL(144)
		MKVNULL(145)
		MKVNULL(146)
		MKVNULL(147)
		MKVNULL(148)
		MKVNULL(149)
		MKVNULL(150)
		MKVNULL(151)
		MKVNULL(152)
		MKVNULL(153)
		MKVNULL(154)
		MKVNULL(155)
		MKVNULL(156)
		MKVNULL(157)
		MKVNULL(158)
		MKVNULL(159)
		MKVNULL(160)
		MKVNULL(161)
		MKVNULL(162)
		MKVNULL(163)
		MKVNULL(164)
		MKVNULL(165)
		MKVNULL(166)
		MKVNULL(167)
		MKVNULL(168)
		MKVNULL(169)
		MKVNULL(170)
		MKVNULL(171)
		MKVNULL(172)
		MKVNULL(173)
		MKVNULL(174)
		MKVNULL(175)
		MKVNULL(176)
		MKVNULL(177)
		MKVNULL(178)
		MKVNULL(179)
		MKVNULL(180)
		MKVNULL(181)
		MKVNULL(182)
		MKVNULL(183)
		MKVNULL(184)
		MKVNULL(185)
		MKVNULL(186)
		MKVNULL(187)
		MKVNULL(188)
		MKVNULL(189)
		MKVNULL(190)
		MKVNULL(191)
		MKVNULL(192)
		MKVNULL(193)
		MKVNULL(194)
		MKVNULL(195)
		MKVNULL(196)
		MKVNULL(197)
		MKVNULL(198)
		MKVNULL(199)
		MKVNULL(200)
		MKVNULL(201)
		MKVNULL(202)
		MKVNULL(203)
		MKVNULL(204)
		MKVNULL(205)
		MKVNULL(206)
		MKVNULL(207)
		MKVNULL(208)
		MKVNULL(209)
		MKVNULL(210)
		MKVNULL(211)
		MKVNULL(212)
		MKVNULL(213)
		MKVNULL(214)
		MKVNULL(215)
		MKVNULL(216)
		MKVNULL(217)
		MKVNULL(218)
		MKVNULL(219)
		MKVNULL(220)
		MKVNULL(221)
		MKVNULL(222)
		MKVNULL(223)
		MKVNULL(224)
		MKVNULL(225)
		MKVNULL(226)
		MKVNULL(227)
		MKVNULL(228)
		MKVNULL(229)
		MKVNULL(230)
		MKVNULL(231)
		MKVNULL(232)
		MKVNULL(233)
		MKVNULL(234)
		MKVNULL(235)
		MKVNULL(236)
		MKVNULL(237)
		MKVNULL(238)
		MKVNULL(239)
		MKVNULL(240)
		MKVNULL(241)
		MKVNULL(242)
		MKVNULL(243)
		MKVNULL(244)
		MKVNULL(245)
		MKVNULL(246)
		MKVNULL(247)
		MKVNULL(248)
		MKVNULL(249)
		MKVNULL(250)
		MKVNULL(251)
		MKVNULL(252)
		MKVNULL(253)
		MKVNULL(254)
		MKVNULL(255)
		MKVNULL(256)
		MKVNULL(257)
		MKVNULL(258)
		MKVNULL(259)
		MKVNULL(260)
		MKVNULL(261)
		MKVNULL(262)
		MKVNULL(263)
		MKVNULL(264)
		MKVNULL(265)
		MKVNULL(266)
		MKVNULL(267)
		MKVNULL(268)
		MKVNULL(269)
		MKVNULL(270)
		MKVNULL(271)
		MKVNULL(272)
		MKVNULL(273)
		MKVNULL(274)
		MKVNULL(275)
		MKVNULL(276)
		MKVNULL(277)
		MKVNULL(278)
		MKVNULL(279)
		MKVNULL(280)
		MKVNULL(281)
		MKVNULL(282)
		MKVNULL(283)
		MKVNULL(284)
		MKVNULL(285)
		MKVNULL(286)
		MKVNULL(287)
		MKVNULL(288)
		MKVNULL(289)
		MKVNULL(290)
		MKVNULL(291)
		MKVNULL(292)
		MKVNULL(293)
		MKVNULL(294)
		MKVNULL(295)
		MKVNULL(296)
		MKVNULL(297)
		MKVNULL(298)
		MKVNULL(299)
		MKVNULL(300)
		MKVNULL(301)
		MKVNULL(302)
		MKVNULL(303)
		MKVNULL(304)
		MKVNULL(305)
		MKVNULL(306)
		MKVNULL(307)
		MKVNULL(308)
		MKVNULL(309)
		MKVNULL(310)
		MKVNULL(311)
		MKVNULL(312)
		MKVNULL(313)
		MKVNULL(314)
		MKVNULL(315)
		MKVNULL(316)
		MKVNULL(317)
		MKVNULL(318)
		MKVNULL(319)
		MKVNULL(320)
		MKVNULL(321)
		MKVNULL(322)
		MKVNULL(323)
		MKVNULL(324)
		MKVNULL(325)
		MKVNULL(326)
		MKVNULL(327)
		MKVNULL(328)
		MKVNULL(329)
		MKVNULL(330)
		MKVNULL(331)
		MKVNULL(332)
		MKVNULL(333)
		MKVNULL(334)
		MKVNULL(335)
		MKVNULL(336)
		MKVNULL(337)
		MKVNULL(338)
		MKVNULL(339)
		MKVNULL(340)
		MKVNULL(341)
		MKVNULL(342)
		MKVNULL(343)
		MKVNULL(344)
		MKVNULL(345)
		MKVNULL(346)
		MKVNULL(347)
		MKVNULL(348)
		MKVNULL(349)
		MKVNULL(350)
		MKVNULL(351)
		MKVNULL(352)
		MKVNULL(353)
		MKVNULL(354)
		MKVNULL(355)
		MKVNULL(356)
		MKVNULL(357)
		MKVNULL(358)
		MKVNULL(359)
		MKVNULL(360)
		MKVNULL(361)
		MKVNULL(362)
		MKVNULL(363)
		MKVNULL(364)
		MKVNULL(365)
		MKVNULL(366)
		MKVNULL(367)
		MKVNULL(368)
		MKVNULL(369)
		MKVNULL(370)
		MKVNULL(371)
		MKVNULL(372)
		MKVNULL(373)
		MKVNULL(374)
		MKVNULL(375)
		MKVNULL(376)
		MKVNULL(377)
		MKVNULL(378)
		MKVNULL(379)
		MKVNULL(380)
		MKVNULL(381)
		MKVNULL(382)
		MKVNULL(383)
		MKVNULL(384)
		MKVNULL(385)
		MKVNULL(386)
		MKVNULL(387)
		MKVNULL(388)
		MKVNULL(389)
		MKVNULL(390)
		MKVNULL(391)
		MKVNULL(392)
		MKVNULL(393)
		MKVNULL(394)
		MKVNULL(395)
		MKVNULL(396)
		MKVNULL(397)
		MKVNULL(398)
		MKVNULL(399)
		MKVNULL(400)
		MKVNULL(401)
		MKVNULL(402)
		MKVNULL(403)
		MKVNULL(404)
		MKVNULL(405)
		MKVNULL(406)
		MKVNULL(407)
		MKVNULL(408)
		MKVNULL(409)
		MKVNULL(410)
		MKVNULL(411)
		MKVNULL(412)
		MKVNULL(413)
		MKVNULL(414)
		MKVNULL(415)
		MKVNULL(416)
		MKVNULL(417)
		MKVNULL(418)
		MKVNULL(419)
		MKVNULL(420)
		MKVNULL(421)
		MKVNULL(422)
		MKVNULL(423)
		MKVNULL(424)
		MKVNULL(425)
		MKVNULL(426)
		MKVNULL(427)
		MKVNULL(428)
		MKVNULL(429)
		MKVNULL(430)
		MKVNULL(431)
		MKVNULL(432)
		MKVNULL(433)
		MKVNULL(434)
		MKVNULL(435)
		MKVNULL(436)
		MKVNULL(437)
		MKVNULL(438)
		MKVNULL(439)
		MKVNULL(440)
		MKVNULL(441)
		MKVNULL(442)
		MKVNULL(443)
		MKVNULL(444)
		MKVNULL(445)
		MKVNULL(446)
		MKVNULL(447)
		MKVNULL(448)
		MKVNULL(449)
		MKVNULL(450)
		MKVNULL(451)
		MKVNULL(452)
		MKVNULL(453)
		MKVNULL(454)
		MKVNULL(455)
		MKVNULL(456)
		MKVNULL(457)
		MKVNULL(458)
		MKVNULL(459)
		MKVNULL(460)
		MKVNULL(461)
		MKVNULL(462)
		MKVNULL(463)
		MKVNULL(464)
		MKVNULL(465)
		MKVNULL(466)
		MKVNULL(467)
		MKVNULL(468)
		MKVNULL(469)
		MKVNULL(470)
		MKVNULL(471)
		MKVNULL(472)
		MKVNULL(473)
		MKVNULL(474)
		MKVNULL(475)
		MKVNULL(476)
		MKVNULL(477)
		MKVNULL(478)
		MKVNULL(479)
		MKVNULL(480)
		MKVNULL(481)
		MKVNULL(482)
		MKVNULL(483)
		MKVNULL(484)
		MKVNULL(485)
		MKVNULL(486)
		MKVNULL(487)
		MKVNULL(488)
		MKVNULL(489)
		MKVNULL(490)
		MKVNULL(491)
		MKVNULL(492)
		MKVNULL(493)
		MKVNULL(494)
		MKVNULL(495)
		MKVNULL(496)
		MKVNULL(497)
		MKVNULL(498)
		MKVNULL(499)
		MKVNULL(500)

};

#endif // INullInterface_h__
