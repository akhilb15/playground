Ball = {}

function Ball:load()
    self.img = love.graphics.newImage("Assets/ball.png")
    self.width = self.img:getWidth()
    self.height = self.img:getHeight()
    self.x = love.graphics.getWidth()/2 - self.width/2
    self.y = love.graphics.getHeight()/2 - self.height/2
    self.speed = 200
    self.xVel = -self.speed
    self.yVel = 0
end

function Ball:update(dt)
    self:move(dt)
    self:collideBoundaries()
    self:collidePlayer()
    self:collideAI()
    self:score()
end

function Ball:move(dt)
    self.x = self.x + self.xVel * dt
    self.y = self.y + self.yVel * dt
end

function Ball:collideBoundaries()
    if self.y < 0 then
        self.y = 0;
        self.yVel = self.yVel * -1
    elseif self.y + self.height > love.graphics.getHeight() then
        self.y = love.graphics.getHeight() - self.height
        self.yVel = self.yVel * -1
    end
end

function Ball:collideAI()
    if checkContact(self, AI) then
        local middleBall = self.y + self.height/2
        local middleAI = AI.y + AI.height/2
        local collisionPosition = middleBall - middleAI
        self.yVel = collisionPosition * 5
        self.xVel = -self.speed
    end
end

function Ball:collidePlayer()
    if checkContact(self, Player) then
        local middleBall = self.y + self.height/2
        local middlePlayer = Player.y + Player.height/2
        local collisionPosition = middleBall - middlePlayer
        self.yVel = collisionPosition * 5
        self.xVel = self.speed
    end
end

function Ball:score()
    if self.x < 0 then
        self:resetPosition()
        self.xVel = self.speed
        Score.ai = Score.ai + 1
    elseif self.x + self.width > love.graphics.getWidth() then
        self:resetPosition()
        self.xVel = -self.speed
        Score.player = Score.player + 1
    end
end

function Ball:resetPosition()
    self.x = love.graphics.getWidth()/2 - self.width/2
    self.y = love.graphics.getHeight()/2 - self.height/2
    self.yVel = 0
end

function Ball:draw()
    love.graphics.draw(self.img, self.x, self.y)
end