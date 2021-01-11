class AttrDict(dict):
    """A dictionary that can be accessed by attributes.

    This should only be used to mock objects for unit testing. Please do not use this outside of qmk.tests.
    """

    def __init__(self, *args, **kwargs):
        super(AttrDict, self).__init__(*args, **kwargs)
        self.__dict__ = self
